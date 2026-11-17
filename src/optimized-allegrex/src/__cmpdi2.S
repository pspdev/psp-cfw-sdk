    .text
    .set noreorder
    .set noat
    .globl __cmpdi2
    .globl __ucmpdi2

# -----------------------------------------------------------------------------
# int __cmpdi2(int64_t a, int64_t b)
# Signed 64-bit comparison: returns 0 (a < b), 1 (a == b), or 2 (a > b)
# -----------------------------------------------------------------------------
    .ent __cmpdi2
__cmpdi2:
    # Compare signed high words first
    slt     $t0, $a1, $a3       # $t0 = 1 if a.high < b.high (signed)
    bnez    $t0, .L_cmp_less
    slt     $t1, $a3, $a1       # (Delay slot) $t1 = 1 if a.high > b.high (signed)
    bnez    $t1, .L_cmp_greater
    nop

    # High words are equal: compare low words UNSIGNED
    sltu    $t0, $a0, $a2       # $t0 = 1 if a.low < b.low (unsigned)
    bnez    $t0, .L_cmp_less
    sltu    $t1, $a2, $a0       # (Delay slot) $t1 = 1 if a.low > b.low (unsigned)
    bnez    $t1, .L_cmp_greater
    nop

    # Equal
    jr      $ra
    li      $v0, 1              # (Delay slot) Return 1 (a == b)
    .end __cmpdi2

# -----------------------------------------------------------------------------
# int __ucmpdi2(uint64_t a, uint64_t b)
# Unsigned 64-bit comparison: returns 0 (a < b), 1 (a == b), or 2 (a > b)
# -----------------------------------------------------------------------------
    .ent __ucmpdi2
__ucmpdi2:
    # Compare unsigned high words first
    sltu    $t0, $a1, $a3       # $t0 = 1 if a.high < b.high (unsigned)
    bnez    $t0, .L_cmp_less
    sltu    $t1, $a3, $a1       # (Delay slot) $t1 = 1 if a.high > b.high (unsigned)
    bnez    $t1, .L_cmp_greater
    nop

    # High words are equal: compare low words UNSIGNED
    sltu    $t0, $a0, $a2       # $t0 = 1 if a.low < b.low (unsigned)
    bnez    $t0, .L_cmp_less
    sltu    $t1, $a2, $a0       # (Delay slot) $t1 = 1 if a.low > b.low (unsigned)
    bnez    $t1, .L_cmp_greater
    nop

    # Equal
    jr      $ra
    li      $v0, 1              # (Delay slot) Return 1 (a == b)

.L_cmp_less:
    jr      $ra
    move    $v0, $zero          # (Delay slot) Return 0 (a < b)

.L_cmp_greater:
    jr      $ra
    li      $v0, 2              # (Delay slot) Return 2 (a > b)
    .end __ucmpdi2
