cmake_minimum_required(VERSION 3.28)

project(bootloadex VERSION 1.0 LANGUAGES C ASM)

add_library(bootloadex_common INTERFACE)
target_sources(bootloadex_common INTERFACE crt0.S main.c lib.c pspbtcnf.c scanner.c rebootex.h)
target_include_directories(bootloadex_common INTERFACE ${CMAKE_CURRENT_LIST_DIR} ${ark-dev-sdk_SOURCE_DIR}/include)
target_link_libraries(bootloadex_common INTERFACE iplsdk)
target_link_options(bootloadex_common INTERFACE -nostdlib -T${CMAKE_CURRENT_LIST_DIR}/linkfile.l)
target_compile_options(bootloadex_common INTERFACE -std=c99 -Os -G0 -Wall -fno-pic)

add_library(bootloadex_psp INTERFACE)
target_sources(bootloadex_psp INTERFACE psp_rebootex/patches.c)
target_link_libraries(bootloadex_psp INTERFACE bootloadex_common)

add_library(bootloadex_vita INTERFACE)
target_sources(bootloadex_vita INTERFACE vita_rebootex/patches.c)
target_link_libraries(bootloadex_vita INTERFACE bootloadex_common)