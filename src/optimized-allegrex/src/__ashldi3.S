    .text
    .set noreorder
    .set noat
    .globl __ashldi3
    .ent __ashldi3

# -----------------------------------------------------------------------------
# uint64_t __ashldi3(uint64_t val, int shift)
#
# Arguments:
#   $a0 : Low 32 bits of val
#   $a1 : High 32 bits of val
#   $a2 : Shift count (0 to 63)
#
# Returns:
#   $v0 : Low 32 bits of result
#   $v1 : High 32 bits of result
#
# Notes:
#   Uses Allegrex's conditional move instructions (movz/movn) to avoid
#   pipeline stalls from branch mispredictions.
# -----------------------------------------------------------------------------
__ashldi3:
    andi    $t0, $a2, 0x20      # Check if shift >= 32 (bit 5 is set)
    subu    $t1, $zero, $a2     # $t1 = -shift (low 5 bits equal 32 - (shift & 31))
    sllv    $v0, $a0, $a2       # Low = low << (shift & 31)
    srlv    $t2, $a0, $t1       # Bits shifted out of low = low >> (32 - (shift & 31))
    sllv    $v1, $a1, $a2       # High = high << (shift & 31)
    movz    $t2, $zero, $t1     # If (shift & 31) == 0, $t1 == 0, so clear $t2 (avoids shift by 32)
    or      $v1, $v1, $t2       # Combine shifted high bits with carry from low bits

    # If shift >= 32 ($t0 != 0), high becomes low, and low becomes 0
    movn    $v1, $v0, $t0       # If shift >= 32, high = $v0
    jr      $ra
    movn    $v0, $zero, $t0     # (Delay slot) If shift >= 32, low = 0

    .end __ashldi3
