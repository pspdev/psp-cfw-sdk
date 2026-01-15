/**
    The core of compressed iso reader.
    Abstracted to be compatible with all formats (CSO/ZSO/JSO/DAX).
    
    All compressed formats have the same overall structure:
    - A header followed by an array of block offsets (uint32).
    
    We only need to know the size of the header and some information from it.
    - block size: the size of a block once uncompressed.
    - uncompressed size: total size of the original (uncompressed) ISO file.
    - block header: size of block header if any (zlib header in DAX, JISO block_header, none for CSO/ZSO).
    - align: CISO block alignment (none for others).
    
    Some other Technical Information:
    - Block offsets can use the top bit to represent aditional information for the decompressor (NCarea, compression method, etc).
    - Block size is calculated via the difference with the next block. Works for DAX, allowing us to skip parsing block size array (with correction for last block).
    - Non-Compressed Area can be determined if size of compressed block is equal to size of uncompressed (equal or greater for CSOv2 due to padding).
    - This reader won't work for CSO/ZSO files above 4GB to avoid using 64 bit arithmetic, but can be easily adjustable.
    - This reader can compile and run on PC and other platforms, as long as reader() is properly implemented.
    
    Includes IO Speed improvements:
    - a cache for block offsets, so we reduce block offset IO.
    - reading the entire compressed data (or chunks of it) at the end of provided buffer to reduce block IO.

*/


#include <string.h>
#include <ciso.h>

#define MIN(x, y) ((x<y)?x:y)

// must be implemented outside
extern int zlib_inflate(void* dst, int dst_len, void* src);
extern int lzo1x_decompress(void*, int, void*, int*, void*);
extern int LZ4_decompress_fast(void* src, void* dst, int dst_len);

// Decompress DAX v0
static void decompress_dax0(void* src, int src_len, void* dst, int dst_len, uint32_t topbit){
    // use raw inflate with no NCarea check
    zlib_inflate(dst, DAX_COMP_BUF, src);
}

// Decompress DAX v1 or JISO method 1
static void decompress_dax1(void* src, int src_len, void* dst, int dst_len, uint32_t topbit){
    // for DAX Version 1 we can skip parsing NC-Areas and just use the block_size trick as in JSO and CSOv2
    if (src_len == dst_len) memcpy(dst, src, dst_len); // check for NC area
    else zlib_inflate(dst, dst_len, src); // use raw inflate
}

// Decompress JISO method 0
static void decompress_jiso(void* src, int src_len, void* dst, int dst_len, uint32_t topbit){
    // while JISO allows for DAX-like NCarea, it by default uses compressed size check
    if (src_len == dst_len) memcpy(dst, src, dst_len); // check for NC area
    else lzo1x_decompress(src, src_len, dst, (int*)&dst_len, 0); // use lzo
}

// Decompress CISO v1
static void decompress_ciso(void* src, int src_len, void* dst, int dst_len, uint32_t topbit){
    if (topbit) memcpy(dst, src, dst_len); // check for NC area
    else zlib_inflate(dst, dst_len, src);
}

// Decompress ZISO
static void decompress_ziso(void* src, int src_len, void* dst, int dst_len, uint32_t topbit){
    if (topbit) memcpy(dst, src, dst_len); // check for NC area
    else LZ4_decompress_fast(src, dst, dst_len);
}

// Decompress CISO v2
static void decompress_cso2(void* src, int src_len, void* dst, int dst_len, uint32_t topbit){
    // in CSOv2, top bit represents compression method instead of NCarea
    if (src_len >= dst_len) memcpy(dst, src, dst_len); // check for NC area (JSO-like, but considering padding, thus >=)
    else if (topbit) LZ4_decompress_fast(src, dst, dst_len);
    else zlib_inflate(dst, dst_len, src);
}

int ciso_open(CisoFile* file)
{
    if (file == NULL || file->read_data == NULL)
        return CISO_BAD_ARGS;
    
    union {
        CISOHeader ciso;
        DAXHeader dax;
        JISOHeader jiso;
    } header;

    *((uint32_t*)&header) = 0;

    if (file->read_data(file->reader_arg, &header, sizeof(header), 0) != sizeof(header)) {
        return CISO_IO_ERROR;
    }

    uint32_t magic = *((uint32_t*)&header);
    if (magic == CSO_MAGIC || magic == ZSO_MAGIC || magic == DAX_MAGIC || magic == JSO_MAGIC) { // CISO or ZISO or JISO or DAX
        uint32_t com_size = 0;
        // set reader and decompressor functions according to format
        if (magic == DAX_MAGIC){
            file->header_size = sizeof(DAXHeader);
            file->block_size = DAX_BLOCK_SIZE; // DAX uses static block size (8K)
            file->uncompressed_size = header.dax.uncompressed_size;
            file->block_header = 2; // skip over the zlib header (2 bytes)
            file->align = 0; // no alignment for DAX
            com_size = DAX_COMP_BUF;
            file->decompressor = (header.dax.version >= 1)? &decompress_dax1 : &decompress_dax0;
        }
        else if (magic == JSO_MAGIC){
            file->header_size = sizeof(JISOHeader);
            file->block_size = header.jiso.block_size;
            file->uncompressed_size = header.jiso.uncompressed_size;
            file->block_header = 4*header.jiso.block_headers; // if set to 1, each block has a 4 byte header, 0 otherwise
            file->align = 0; // no alignment for JISO
            com_size = header.jiso.block_size;
            file->decompressor = (header.jiso.method)? &decompress_dax1 : &decompress_jiso; //  zlib or lzo, depends on method
        }
        else{ // CSO/ZSO/v2
            file->header_size = sizeof(CISOHeader);
            file->block_size = header.ciso.block_size;
            file->uncompressed_size = header.ciso.total_bytes;
            file->block_header = 0; // CSO/ZSO uses raw blocks
            file->align = header.ciso.align;
            com_size = file->block_size + (1 << header.ciso.align);
            if (header.ciso.ver == 2) file->decompressor = &decompress_cso2; // CSOv2 uses both zlib and lz4
            else file->decompressor = (magic == ZSO_MAGIC)? &decompress_ziso : &decompress_ciso; // CSO/ZSO v1 (zlib or lz4)
        }

        // for files with higher block sizes, we can reduce block cache size
        int ratio = file->block_size/ISO_SECTOR_SIZE;
        file->idx_cache_num = CISO_IDX_MAX_ENTRIES/ratio;

        // calculate total number of ciso blocks
        file->total_blocks = file->uncompressed_size / file->block_size;
        
        // allocate memory if needed
        if (file->dec_buf == NULL){
            file->dec_buf = file->memalign(64, com_size);
        }

        if (file->block_buf == NULL){
            file->block_buf = file->memalign(64, com_size);
        }

        if (file->idx_cache == NULL){
            file->idx_cache = file->memalign(64, file->idx_cache_num * 4);
            file->idx_start_block = -1;
        }

        // all done
        return 1;
    }
    // not a valid file
    return 0;
}

int ciso_read(CisoFile* file, uint8_t* addr, uint32_t size, uint32_t offset)
{
    uint32_t cur_block;
    uint32_t pos, read_bytes;
    uint32_t o_offset = offset;
    uint8_t* com_buf = file->block_buf;
    uint8_t* dec_buf = file->dec_buf;
    uint8_t* c_buf = NULL;
    uint8_t* top_addr = addr+size;
    
    if(offset > file->uncompressed_size) {
        // return if the offset goes beyond the iso size
        return 0;
    }
    else if(offset + size > file->uncompressed_size) {
        // adjust size if it tries to read beyond the game data
        size = file->uncompressed_size - offset;
    }

    // IO speedup tricks
    uint32_t starting_block = o_offset / file->block_size;
    uint32_t ending_block = ((o_offset+size)/file->block_size);
    
    // refresh index table if needed
    if (file->idx_start_block < 0 || starting_block < file->idx_start_block || starting_block-file->idx_start_block+1 >= file->idx_cache_num-1){
        file->read_data(
            file->reader_arg,
            (uint8_t*)file->idx_cache,
            file->idx_cache_num*sizeof(uint32_t),
            starting_block * sizeof(uint32_t) + file->header_size
        );
        file->idx_start_block = starting_block;
    }

    // Calculate total size of compressed data
    uint32_t o_start = (file->idx_cache[starting_block-file->idx_start_block]&0x7FFFFFFF)<<file->align;
    // last block index might be outside the block offset cache, better read it from disk
    uint32_t o_end;
    if (ending_block-file->idx_start_block < file->idx_cache_num-1){
        o_end = file->idx_cache[ending_block-file->idx_start_block];
    }
    else { // read last two offsets
        file->read_data(
            file->reader_arg,
            (uint8_t*)&o_end,
            sizeof(uint32_t),
            ending_block*sizeof(uint32_t) + file->header_size
        );
    }
    o_end = (o_end&0x7FFFFFFF)<<file->align;
    uint32_t compressed_size = o_end-o_start;

    // try to read at once as much compressed data as possible
    if (size > file->block_size*2){ // only if going to read more than two blocks
        if (size < compressed_size) compressed_size = size-file->block_size; // adjust chunk size if compressed data is still bigger than uncompressed
        c_buf = top_addr - compressed_size; // read into the end of the user buffer
        file->read_data(file->reader_arg, c_buf, compressed_size, o_start);
    }

    while(size > 0) {
        // calculate block number and offset within block
        cur_block = offset / file->block_size;
        pos = offset & (file->block_size - 1);

        // check if we need to refresh index table
        if (cur_block-file->idx_start_block >= file->idx_cache_num-1){
            file->read_data(
                file->reader_arg,
                (uint8_t*)file->idx_cache,
                file->idx_cache_num*sizeof(uint32_t),
                cur_block*sizeof(uint32_t) + file->header_size
            );
            file->idx_start_block = cur_block;
        }
        
        // read compressed block offset and size
        uint32_t b_offset = file->idx_cache[cur_block-file->idx_start_block];
        uint32_t b_size = file->idx_cache[cur_block-file->idx_start_block+1];
        uint32_t topbit = b_offset&0x80000000; // extract top bit for decompressor
        b_offset = (b_offset&0x7FFFFFFF) << file->align;
        b_size = (b_size&0x7FFFFFFF) << file->align;
        b_size -= b_offset;

        if (cur_block == file->total_blocks-1 && file->header_size == sizeof(DAXHeader))
            // fix for last DAX block (you can't trust the value of b_size since there's no offset for last_block+1)
            b_size = DAX_COMP_BUF;

        // check if we need to (and can) read another chunk of data
        if (c_buf < addr || c_buf+b_size > top_addr){
            if (size > b_size+file->block_size){ // only if more than two blocks left, otherwise just use normal reading
                compressed_size = o_end-b_offset; // recalculate remaining compressed data
                if (size < compressed_size) compressed_size = size-file->block_size; // adjust if still bigger than uncompressed
                if (compressed_size >= b_size){
                    c_buf = top_addr - compressed_size; // read into the end of the user buffer
                    file->read_data(file->reader_arg, c_buf, compressed_size, b_offset);
                }
            }
        }

        // read block, skipping header if needed
        if (c_buf >= addr && c_buf+b_size <= top_addr){
            memcpy(com_buf, c_buf+file->block_header, b_size); // fast read
            c_buf += b_size;
        }
        else{ // slow read
            b_size = file->read_data(file->reader_arg, com_buf, b_size, b_offset + file->block_header);
            if (c_buf) c_buf += b_size;
        }

        // decompress block
        file->decompressor(com_buf, b_size, dec_buf, file->block_size, topbit);
    
        // read data from block into buffer
        read_bytes = MIN(size, (file->block_size - pos));
        memcpy(addr, dec_buf + pos, read_bytes);
        size -= read_bytes;
        addr += read_bytes;
        offset += read_bytes;
    }

    return offset - o_offset;
}

int ciso_close(CisoFile* file){
    if (file){
        if (file->memalign && file->free){
            if (file->dec_buf){
                file->free(file->dec_buf);
                file->dec_buf = NULL;
            }
            if (file->block_buf){
                file->free(file->block_buf);
                file->block_buf = NULL;
            }
            if (file->idx_cache){
                file->free(file->idx_cache);
                file->idx_cache = NULL;
            }
        }
        file->idx_start_block = -1;
        return CISO_OK;
    }
    return CISO_BAD_ARGS;
}
