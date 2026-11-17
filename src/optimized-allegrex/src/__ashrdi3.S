    .text
    .set noreorder
    .set noat
    .globl __ashrdi3
    .ent __ashrdi3

# -----------------------------------------------------------------------------
# int64_t __ashrdi3(int64_t val, int shift)
# -----------------------------------------------------------------------------
__ashrdi3:
    andi    $t0, $a2, 0x20      # Check if shift >= 32
    subu    $t1, $zero, $a2     # $t1 = -shift (low 5 bits equal 32 - (shift & 31))
    srlv    $v0, $a0, $a2       # Low = low >> (shift & 31) (logical shift)
    sllv    $t2, $a1, $t1       # Bits shifted out of high = high << (32 - (shift & 31))
    srav    $v1, $a1, $a2       # High = high >> (shift & 31) (arithmetic shift)
    movz    $t2, $zero, $t1     # If (shift & 31) == 0, clear $t2
    or      $v0, $v0, $t2       # Combine shifted low bits with carry from high bits

    # Prepare sign-filled word (0xFFFFFFFF if negative, 0x00000000 if positive)
    sra     $t3, $a1, 31        # $t3 = sign mask of high word

    # If shift >= 32 ($t0 != 0), low becomes arithmetic-shifted high, high becomes sign mask
    movn    $v0, $v1, $t0       # If shift >= 32, low = $v1
    jr      $ra
    movn    $v1, $t3, $t0       # (Delay slot) If shift >= 32, high = sign mask

    .end __ashrdi3
