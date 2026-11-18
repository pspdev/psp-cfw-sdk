    .text
    .set noreorder
    .set noat
    .globl __muldi3
    .ent __muldi3

# -----------------------------------------------------------------------------
# uint64_t __muldi3(uint64_t a, uint64_t b)
#
# Arguments:
#   $a0 : Low 32 bits of a
#   $a1 : High 32 bits of a
#   $a2 : Low 32 bits of b
#   $a3 : High 32 bits of b
#
# Returns:
#   $v0 : Low 32 bits of (a * b)
#   $v1 : High 32 bits of (a * b)
#
# Formula:
#   result = (a.low * b.low) + (((a.low * b.high) + (a.high * b.low)) << 32)
# -----------------------------------------------------------------------------
__muldi3:
    multu   $a0, $a2            # HI:LO = a.low * b.low
    mflo    $v0                 # $v0 = low 32 bits of result
    mfhi    $v1                 # $v1 = carry into high 32 bits
    mthi    $zero               # Clear HI so maddu accumulates into LO only
    mtlo    $v1                 # Seed LO with the carry from (a.low * b.low)
    maddu   $a0, $a3            # LO += (a.low * b.high)
    maddu   $a1, $a2            # LO += (a.high * b.low)
    jr      $ra
    mflo    $v1                 # (Delay slot) $v1 = high 32 bits of result

    .end __muldi3
