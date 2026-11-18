    .text
    .set noreorder
    .set noat
    .globl __lshrdi3
    .ent __lshrdi3

# -----------------------------------------------------------------------------
# uint64_t __lshrdi3(uint64_t val, int shift)
# -----------------------------------------------------------------------------
__lshrdi3:
    andi    $t0, $a2, 0x20      # Check if shift >= 32
    subu    $t1, $zero, $a2     # $t1 = -shift (low 5 bits equal 32 - (shift & 31))
    srlv    $v0, $a0, $a2       # Low = low >> (shift & 31)
    sllv    $t2, $a1, $t1       # Bits shifted out of high = high << (32 - (shift & 31))
    srlv    $v1, $a1, $a2       # High = high >> (shift & 31)
    movz    $t2, $zero, $t1     # If (shift & 31) == 0, clear $t2 (avoids shift by 32)
    or      $v0, $v0, $t2       # Combine shifted low bits with carry from high bits

    # If shift >= 32 ($t0 != 0), low becomes high, and high becomes 0
    movn    $v0, $v1, $t0       # If shift >= 32, low = $v1
    jr      $ra
    movn    $v1, $zero, $t0     # (Delay slot) If shift >= 32, high = 0

    .end __lshrdi3
