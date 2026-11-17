    .text
    .set noreorder
    .set noat
    .globl __bswapsi2
    .globl __bswapdi2

# -----------------------------------------------------------------------------
# uint32_t __bswapsi2(uint32_t x)
# 32-bit endian byte swap
# -----------------------------------------------------------------------------
    .ent __bswapsi2
__bswapsi2:
    wsbh    $v0, $a0            # Swap bytes in each 16-bit halfword
    jr      $ra
    rotr    $v0, $v0, 16        # (Delay slot) Swap the two 16-bit halfwords
    .end __bswapsi2

# -----------------------------------------------------------------------------
# uint64_t __bswapdi2(uint64_t x)
# 64-bit endian byte swap ($a1:$a0 -> $v1:$v0)
# -----------------------------------------------------------------------------
    .ent __bswapdi2
__bswapdi2:
    wsbh    $v1, $a0            # Swap low word bytes -> goes to high word ($v1)
    wsbh    $v0, $a1            # Swap high word bytes -> goes to low word ($v0)
    rotr    $v1, $v1, 16
    jr      $ra
    rotr    $v0, $v0, 16        # (Delay slot)
    .end __bswapdi2
