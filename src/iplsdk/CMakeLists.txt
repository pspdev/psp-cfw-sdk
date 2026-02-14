add_sdk_library(iplsdk STATIC)

target_include_directories(iplsdk PUBLIC include)

target_sources(iplsdk PRIVATE
   src/cache.S
   src/cpu.S
   src/display.c
   src/dmacplus.c
   src/emcddr.c
   src/chip.c
   src/ecc.c
   src/emcsm.c
   src/scramble.c
   src/state.c
   src/exception.c
   src/exception_asm.S
   src/gpio.c
   src/interrupt.c
   src/interrupt_asm.S
   src/kirk.c
   src/lcd.c
   src/phatlcd.c
   src/hibari.c
   src/samantha.c
   src/streetlcd.c
   src/tmdlcd.c
   src/lcdc.c
   src/led.c
   src/lflash.c
   src/model.c
   src/mspro.c
   src/ms.c
   src/pwm.c
   src/spi.c
   src/comms.c
   src/handshake.c
   src/syscon.c
   src/sysreg.c
   src/uart.c
   src/delay.S
   src/fat.c
   src/utils.c
)

target_compile_options(iplsdk PRIVATE -fdata-sections -ffunction-sections -Wl,--gc-sections)

add_custom_command(TARGET iplsdk POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E make_directory "${SDK_INCLUDE_DIR}/iplsdk"
   COMMAND cp "$<TARGET_FILE:iplsdk>" "${SDK_LIBS_DIR}/"
   COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${SDK_INCLUDE_DIR}/iplsdk/"
   COMMENT "Copying lib and headers"
)