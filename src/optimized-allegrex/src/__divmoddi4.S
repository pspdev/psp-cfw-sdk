    .text
    .set noreorder
    .set noat
    .globl __divdi3
    .globl __moddi3
    .globl __divmoddi4

# -----------------------------------------------------------------------------
# int64_t __divdi3(int64_t num, int64_t den)
# Returns signed quotient in $v1:$v0
# -----------------------------------------------------------------------------
    .ent __divdi3
__divdi3:
    addiu   $sp, $sp, -24
    sw      $ra, 20($sp)
    sw      $s0, 16($sp)

    xor     $s0, $a1, $a3
    sra     $s0, $s0, 31        # Quotient sign mask

    bgez    $a1, .L_div_check_den
    nop
    subu    $a0, $zero, $a0
    sltu    $t0, $zero, $a0
    subu    $a1, $zero, $a1
    subu    $a1, $a1, $t0

.L_div_check_den:
    bgez    $a3, .L_div_call
    nop
    subu    $a2, $zero, $a2
    sltu    $t0, $zero, $a2
    subu    $a3, $zero, $a3
    subu    $a3, $a3, $t0

.L_div_call:
    jal     __udivdi3
    nop

    beqz    $s0, .L_div_done
    nop
    subu    $v0, $zero, $v0
    sltu    $t0, $zero, $v0
    subu    $v1, $zero, $v1
    subu    $v1, $v1, $t0

.L_div_done:
    lw      $s0, 16($sp)
    lw      $ra, 20($sp)
    jr      $ra
    addiu   $sp, $sp, 24        # (Delay slot)
    .end __divdi3

# -----------------------------------------------------------------------------
# int64_t __moddi3(int64_t num, int64_t den)
# Returns signed remainder in $v1:$v0
# -----------------------------------------------------------------------------
    .ent __moddi3
__moddi3:
    addiu   $sp, $sp, -24
    sw      $ra, 20($sp)
    sw      $s0, 16($sp)

    sra     $s0, $a1, 31        # Remainder sign mask (matches num)

    bgez    $a1, .L_mod_check_den
    nop
    subu    $a0, $zero, $a0
    sltu    $t0, $zero, $a0
    subu    $a1, $zero, $a1
    subu    $a1, $a1, $t0

.L_mod_check_den:
    bgez    $a3, .L_mod_call
    nop
    subu    $a2, $zero, $a2
    sltu    $t0, $zero, $a2
    subu    $a3, $zero, $a3
    subu    $a3, $a3, $t0

.L_mod_call:
    jal     __umoddi3
    nop

    beqz    $s0, .L_mod_done
    nop
    subu    $v0, $zero, $v0
    sltu    $t0, $zero, $v0
    subu    $v1, $zero, $v1
    subu    $v1, $v1, $t0

.L_mod_done:
    lw      $s0, 16($sp)
    lw      $ra, 20($sp)
    jr      $ra
    addiu   $sp, $sp, 24        # (Delay slot)
    .end __moddi3

# -----------------------------------------------------------------------------
# int64_t __divmoddi4(int64_t num, int64_t den, int64_t *rem)
#
# Arguments:
#   $a1:$a0 : num
#   $a3:$a2 : den
#   16($sp) : int64_t *rem (may be NULL)
#
# Returns:
#   $v1:$v0 : signed quotient (and writes signed remainder to *rem if != NULL)
# -----------------------------------------------------------------------------
    .ent __divmoddi4
__divmoddi4:
    # Stack frame layout (48 bytes, 8-byte aligned):
    #   44($sp) : saved $ra
    #   40($sp) : saved $s0 (quotient sign mask)
    #   36($sp) : saved $s1 (remainder sign mask = num sign)
    #   32($sp) : saved $s2 (caller's int64_t *rem pointer)
    #   24($sp) : temporary uint64_t unsigned_rem (8 bytes)
    #   16($sp) : outgoing arg 5 (&unsigned_rem) for __udivmoddi4
    #   0..15   : O32 argument home area
    lw      $t2, 16($sp)        # Load caller's rem pointer BEFORE adjusting $sp
    addiu   $sp, $sp, -48
    sw      $ra, 44($sp)
    sw      $s0, 40($sp)
    sw      $s1, 36($sp)
    sw      $s2, 32($sp)

    move    $s2, $t2            # $s2 = caller's rem pointer
    xor     $s0, $a1, $a3
    sra     $s0, $s0, 31        # $s0 = quotient sign mask
    sra     $s1, $a1, 31        # $s1 = remainder sign mask

    # Abs(num)
    bgez    $a1, .L_divmod_check_den
    nop
    subu    $a0, $zero, $a0
    sltu    $t0, $zero, $a0
    subu    $a1, $zero, $a1
    subu    $a1, $a1, $t0

.L_divmod_check_den:
    # Abs(den)
    bgez    $a3, .L_divmod_call
    nop
    subu    $a2, $zero, $a2
    sltu    $t0, $zero, $a2
    subu    $a3, $zero, $a3
    subu    $a3, $a3, $t0

.L_divmod_call:
    # Pass pointer to local 8-byte buffer at 24($sp) if caller's rem != NULL, else NULL
    addiu   $t0, $sp, 24
    movz    $t0, $zero, $s2
    sw      $t0, 16($sp)

    jal     __udivmoddi4
    nop

    # Apply quotient sign ($s0) to $v1:$v0
    beqz    $s0, .L_divmod_rem
    nop
    subu    $v0, $zero, $v0
    sltu    $t0, $zero, $v0
    subu    $v1, $zero, $v1
    subu    $v1, $v1, $t0

.L_divmod_rem:
    # If caller's rem ($s2) == NULL, skip remainder store
    beqz    $s2, .L_divmod_done
    nop

    lw      $t0, 24($sp)        # unsigned_rem.low
    lw      $t1, 28($sp)        # unsigned_rem.high

    # Apply remainder sign ($s1) if num was negative
    beqz    $s1, .L_divmod_store_rem
    nop
    subu    $t0, $zero, $t0
    sltu    $t2, $zero, $t0
    subu    $t1, $zero, $t1
    subu    $t1, $t1, $t2

.L_divmod_store_rem:
    sw      $t0, 0($s2)
    sw      $t1, 4($s2)

.L_divmod_done:
    lw      $s2, 32($sp)
    lw      $s1, 36($sp)
    lw      $s0, 40($sp)
    lw      $ra, 44($sp)
    jr      $ra
    addiu   $sp, $sp, 48        # (Delay slot)
    .end __divmoddi4
