#ifndef __OPTIMIZED__psp_H__
#define __OPTIMIZED__psp_H__

/**
 * A Header containing inline functions for Allegrex extended instructions.
 */

#include <psptypes.h>

/** Returns the smaller operand using Allegrex's signed 32-bit comparison (branchless). */
static inline u32 _psp_min(u32 a, u32 b) {
    u32 res;
    __asm__ ("min %0, %1, %2" : "=r"(res) : "r"(a), "r"(b));
    return res;
}

/** Returns the larger operand using Allegrex's signed 32-bit comparison. */
static inline u32 _psp_max(u32 a, u32 b) {
    u32 res;
    __asm__ ("max %0, %1, %2" : "=r"(res) : "r"(a), "r"(b));
    return res;
}

/**
 * Clamps val to the inclusive range `[lo, hi]`, using Allegrex's signed
 * 32-bit comparisons (branchless).
 *
 * @pre lo <= hi.
 */
static inline u32 _psp_clamp(u32 val, u32 lo, u32 hi) {
    u32 res;
    __asm__ (
        "max %0, %1, %2\n\t"
        "min %0, %0, %3"
        : "=&r"(res)
        : "r"(val), "r"(lo), "r"(hi)
    );
    return res;
}

/**
 * Extracts bits from a value starting at a bit position and zero-extends the result.
 *
 * @param pos The bit position to start. Valid range in `[0, 31]`.
 * @param size The size of bits to extract. Valid range in `[1, 32]`, with `pos + size <= 32`.
 *
 * @returns The extracted bit range.
 */
static inline u32 _psp_ext(u32 val, const u8 pos, const u8 size) {
    u32 res;
    __asm__ ("ext %0, %1, %2, %3"
        : "=r"(res)
        : "r"(val), "I"(pos), "I"(size)
    );
    return res;
}

/**
 * Inserts bits in the destination value starting at a bit position with the low size
 * bits of the source value; all other bits of the destination value are preserved.
 *
 * @param dst The destination value.
 * @param src The source value.
 * @param pos The bit position to start. Valid range in `[0, 31]`.
 * @param size The size of bits to extract. Valid range in `[1, 32]`, with `pos + size <= 32`.
 *
 * @returns The updated destination value
 */
static inline u32 _psp_ins(u32 dst, u32 src, const u32 pos, const u32 size) {
    __asm__ ("ins %0, %1, %2, %3"
        : "+r"(dst)
        : "r"(src), "I"(pos), "I"(size)
    );
    return dst;
}

/**
 * Reverses the byte order of a value in one CPU cycle.
 *
 * E.g.: 0x12345678 -> 0x78563412
 */
static inline u32 _psp_bswap32(u32 x) {
    u32 res;
    __asm__ ("wsbw %0, %1" : "=r"(res) : "r"(x));
    return res;
}

/**
 * Swaps the bytes within each 16-bit halfword of a value.
 *
 * E.g.: 0x12345678 -> 0x34127856
 */
static inline u32 _psp_bswap16_pair(u32 x) {
    u32 res;
    __asm__ ("wsbh %0, %1" : "=r"(res) : "r"(x));
    return res;
}

/**
 * Reverses the order of all 32 bits in a value in one CPU cycle.
 *
 * E.g.: 0x12345678 -> 0x87654321
 */
static inline u32 _psp_bitrev(u32 x) {
    u32 res;
    __asm__ ("bitrev %0, %1" : "=r"(res) : "r"(x));
    return res;
}

/**
 * Counts leading zero bits in a value.
 *
 * @returns
 *  The count of leading zeroes bits.
 *  `32` when the value is zero.
 */
static inline u32 _psp_clz(u32 x) {
    u32 res;
    __asm__ ("clz %0, %1" : "=r"(res) : "r"(x));
    return res;
}

/**
 * Counts leading one bits in a value.
 *
 * @returns
 *  The count of leading ones bits.
 *  `32` when the value is `UINT32_MAX`.
 */
static inline u32 _psp_clo(u32 x) {
    u32 res;
    __asm__ ("clo %0, %1" : "=r"(res) : "r"(x));
    return res;
}

/** Sign-extends the low 8 bits of a value to a 32-bit signed integer. */
static inline s32 _psp_sext8(u32 x) {
    s32 res;
    __asm__ ("seb %0, %1" : "=r"(res) : "r"(x));
    return res;
}

/** Sign-extends the low 16 bits of a value to a 32-bit signed integer.  */
static inline s32 _psp_sext16(u32 x) {
    s32 res;
    __asm__ ("seh %0, %1" : "=r"(res) : "r"(x));
    return res;
}

#endif /* __OPTIMIZED__psp_H__ */