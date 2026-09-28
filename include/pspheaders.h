#ifndef PSP_HEADERS_H
#define PSP_HEADERS_H

#include <pspsdk.h>

typedef struct
{
    u16        attribute;
    u8        module_ver_lo;
    u8        module_ver_hi;
    char    modname[28];
} __attribute__((packed)) PspModuleInfo;

typedef struct
{
    u32 signature;          //0
    u16 mod_attribute;      //4
    u16 comp_attribute;     //6
    u8 module_ver_lo;       //8
    u8 module_ver_hi;       //9
    char modname[28];       //0xA
    u8 mod_version;         //0x26
    u8 nsegments;           //0x27
    u32 elf_size;           //0x28
    u32 psp_size;           //0x2C
    u32 boot_entry;         //0x30
    u32 modinfo_offset; //0x34
    int bss_size;           //0x38
    u32 seg_align[4];       //0x3C
    u32 seg_address[4];     //0x44
    int seg_size[4];        //0x54
    u32 reserved[5];        //0x64
    u32 devkit_version;     //0x78
    u8 decrypt_mode;        //0x7C
    u8 padding;                     //0x7D
    u8 overlap_size;        //0x7E
    u8 key_data[0x30];      //0x80
    u32 comp_size;          //0xB0
    int _80;                        //0xB4
    u32 unk_B8;                     //0xB8
    u32 unk_BC;                     //0xBC
    u8 key_data2[0x10];     //0xC0
    u32 tag;                        //0xD0
    u8 scheck[0x58];        //0xD4
    u8 sha1_hash[0x14];     //0x12C
    u8 key_data4[0x10]; //0x140
} PSP_Header2; //0x150


typedef struct
{
    u32                signature;  // 0
    PspModuleInfo   mod_info; //4
    u8                version; // 26
    u8                nsegments; // 27
    int                elf_size; // 28
    int                psp_size; // 2C
    u32                entry;    // 30
    u32                modinfo_offset; // 34
    int                bss_size; // 38
    u16                seg_align[4]; // 3C
    u32                seg_address[4]; // 44
    int                seg_size[4]; // 54
    u32                reserved[5]; // 64
    u32                devkitversion; // 78
    u32                decrypt_mode; // 7C
    u8                key_data0[0x30]; // 80
    int                comp_size; // B0
    int                _80;    // B4
    int                reserved2[2];    // B8
    u8                key_data1[0x10]; // C0
    u32                tag; // D0
    u8                scheck[0x58]; // D4
    u32                key_data2; // 12C
    u32                oe_tag; // 130
    u8                key_data3[0x1C]; // 134
} __attribute__((packed)) PSP_Header;


typedef struct
{
    u8 signature[4]; //0
    u16 mod_attribute; //4
    u16 comp_attribute; //6
    u8 module_ver_lo; //8
    u8 module_ver_hi; //9
    char modname[28]; //A
    u8 mod_version; //26
    u8 nsegments; //27
    u32 elf_size; //28
    u32 psp_size; //2C
    u32 boot_entry; //30
    u32 modinfo_offset; //34
    u32 bss_size; //38
    u16 seg_align[4]; //3C
    u32 seg_address[4]; //44
    u32 seg_size[4]; //54
    u32 reserved[5]; //64
    u32 devkit_version; //78
    u8 decrypt_mode; //7C
    u8 padding; //7D
    u16 overlap_size; //7E
    u8 aes_key[0x10]; //80
    u8 cmac_key[0x10]; //90
    u8 cmac_header_hash[0x10]; //A0
    u32 comp_size; //B0
    u32 _80; //B4
    u32 unk_B8; //B8
    u32 unk_BC; //BC
    u8 cmac_data_hash[0x10]; //C0
    u32 tag; //D0
    u8 scheck[0x58]; //D4
    u8 sha1_hash[0x14]; //12C
    u8 key_data4[0x10]; //140
} PSP_HEADER, *LPPSP_HEADER;

#endif