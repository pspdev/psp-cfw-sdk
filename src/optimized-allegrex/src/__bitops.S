    .text
    .set noreorder
    .set noat
    .globl __clzsi2
    .globl __ctzsi2
    .globl __clzdi2
    .globl __ctzdi2

# -----------------------------------------------------------------------------
# int __clzsi2(uint32_t x)
# Count leading zeros in a 32-bit word (x == 0 returns 32)
# -----------------------------------------------------------------------------
    .ent __clzsi2
__clzsi2:
    jr      $ra
    clz     $v0, $a0            # (Delay slot) Hardware CLZ
    .end __clzsi2

# -----------------------------------------------------------------------------
# int __ctzsi2(uint32_t x)
# Count trailing zeros in a 32-bit word (x == 0 returns 32)
# -----------------------------------------------------------------------------
    .ent __ctzsi2
__ctzsi2:
    subu    $t0, $zero, $a0     # $t0 = -x
    and     $t0, $a0, $t0       # Isolate lowest set bit: x & -x
    clz     $t0, $t0            # Leading zeros before lowest set bit (32 if x == 0)
    li      $v0, 31
    subu    $v0, $v0, $t0       # 31 - clz(x & -x)  (gives -1 if x == 0)
    li      $t1, 32
    jr      $ra
    movz    $v0, $t1, $a0       # (Delay slot) If x == 0, return 32
    .end __ctzsi2

# -----------------------------------------------------------------------------
# int __clzdi2(uint64_t x)
# Count leading zeros in a 64-bit doubleword ($a1 = high, $a0 = low)
# -----------------------------------------------------------------------------
    .ent __clzdi2
__clzdi2:
    clz     $v0, $a1            # Count leading zeros in high word
    clz     $t0, $a0            # Count leading zeros in low word
    addiu   $t0, $t0, 32        # Total if high word == 0
    jr      $ra
    movz    $v0, $t0, $a1       # (Delay slot) If high == 0, use 32 + clz(low)
    .end __clzdi2

# -----------------------------------------------------------------------------
# int __ctzdi2(uint64_t x)
# Count trailing zeros in a 64-bit doubleword ($a1 = high, $a0 = low)
# -----------------------------------------------------------------------------
    .ent __ctzdi2
__ctzdi2:
    # Select active word: $a0 if $a0 != 0, else $a1
    move    $t2, $a0
    movz    $t2, $a1, $a0       # $t2 = ($a0 != 0) ? $a0 : $a1

    # Compute 32-bit ctz($t2)
    subu    $t0, $zero, $t2
    and     $t0, $t2, $t0
    clz     $t0, $t0
    li      $v0, 31
    subu    $v0, $v0, $t0       # 31 - clz(lowest_bit)

    # Add 32 if low word ($a0) was zero
    addiu   $t1, $v0, 32
    movz    $v0, $t1, $a0       # If $a0 == 0, add 32 (if both 0, -1 + 32 = 31 -> fixed below)

    # Handle x == 0 ($t2 == 0 -> returns 64)
    li      $t1, 64
    jr      $ra
    movz    $v0, $t1, $t2       # (Delay slot) If both words == 0, return 64
    .end __ctzdi2
