    .text
    .set noreorder
    .set noat
    .globl __udivdi3
    .globl __umoddi3
    .globl __udivmoddi4

# -----------------------------------------------------------------------------
# uint64_t __udivdi3(uint64_t num, uint64_t den)
# Returns quotient in $v1:$v0
# -----------------------------------------------------------------------------
    .ent __udivdi3
__udivdi3:
    move    $t6, $zero          # rem_ptr = NULL
    or      $t0, $a1, $a3
    bnez    $t0, .L_udiv64_slow
    move    $t4, $zero          # (Delay slot) $t4 = 0 (return quotient)

    divu    $zero, $a0, $a2
    mflo    $v0
    jr      $ra
    move    $v1, $zero          # (Delay slot)
    .end __udivdi3

# -----------------------------------------------------------------------------
# uint64_t __umoddi3(uint64_t num, uint64_t den)
# Returns remainder in $v1:$v0
# -----------------------------------------------------------------------------
    .ent __umoddi3
__umoddi3:
    move    $t6, $zero          # rem_ptr = NULL
    or      $t0, $a1, $a3
    bnez    $t0, .L_udiv64_slow
    li      $t4, 1              # (Delay slot) $t4 = 1 (return remainder)

    divu    $zero, $a0, $a2
    mfhi    $v0
    jr      $ra
    move    $v1, $zero          # (Delay slot)
    .end __umoddi3

# -----------------------------------------------------------------------------
# uint64_t __udivmoddi4(uint64_t num, uint64_t den, uint64_t *rem)
#
# Arguments:
#   $a1:$a0 : num
#   $a3:$a2 : den
#   16($sp) : rem pointer (may be NULL)
#
# Returns:
#   $v1:$v0 : quotient (and writes remainder to *rem if rem != NULL)
# -----------------------------------------------------------------------------
    .ent __udivmoddi4
__udivmoddi4:
    lw      $t6, 16($sp)        # Load uint64_t *rem from O32 stack arg 5
    or      $t0, $a1, $a3
    bnez    $t0, .L_udiv64_slow
    move    $t4, $zero          # (Delay slot) $t4 = 0 (return quotient)

    # 32-bit hardware fast path
    divu    $zero, $a0, $a2
    mflo    $v0                 # Quotient low
    move    $v1, $zero          # Quotient high = 0
    beqz    $t6, .L_udivmod_fast_ret
    mfhi    $t0                 # (Delay slot) Remainder low

    sw      $t0, 0($t6)         # *rem.low  = remainder
    sw      $zero, 4($t6)       # *rem.high = 0

.L_udivmod_fast_ret:
    jr      $ra
    nop
    .end __udivmoddi4

# -----------------------------------------------------------------------------
# Shared 64-bit Restoring Binary Long Division
#
# Registers:
#   $a1:$a0 : Dividend -> shifts into Quotient
#   $a3:$a2 : Divisor
#   $t1:$t0 : Remainder
#   $t2     : Loop counter (64)
#   $t4     : Return selector (0 = quotient, 1 = remainder)
#   $t6     : Optional uint64_t *rem pointer (0 if unused)
# -----------------------------------------------------------------------------
.L_udiv64_slow:
    move    $t0, $zero
    move    $t1, $zero
    li      $t2, 64

.L_udiv64_loop:
    srl     $t3, $a1, 31
    sll     $t1, $t1, 1
    srl     $t5, $t0, 31
    or      $t1, $t1, $t5
    sll     $t0, $t0, 1
    or      $t0, $t0, $t3

    srl     $t3, $a0, 31
    sll     $a1, $a1, 1
    or      $a1, $a1, $t3
    sll     $a0, $a0, 1

    sltu    $t3, $t1, $a3
    bnez    $t3, .L_udiv64_next
    nop

    bne     $t1, $a3, .L_udiv64_sub
    sltu    $t3, $t0, $a2       # (Delay slot)
    bnez    $t3, .L_udiv64_next
    nop

.L_udiv64_sub:
    sltu    $t3, $t0, $a2
    subu    $t0, $t0, $a2
    subu    $t1, $t1, $a3
    subu    $t1, $t1, $t3
    ori     $a0, $a0, 1

.L_udiv64_next:
    addiu   $t2, $t2, -1
    bnez    $t2, .L_udiv64_loop
    nop

    # Store remainder to *rem if $t6 != NULL
    beqz    $t6, .L_udiv64_select
    nop
    sw      $t0, 0($t6)
    sw      $t1, 4($t6)

.L_udiv64_select:
    movz    $v0, $a0, $t4
    movz    $v1, $a1, $t4
    movn    $v0, $t0, $t4
    jr      $ra
    movn    $v1, $t1, $t4       # (Delay slot)
