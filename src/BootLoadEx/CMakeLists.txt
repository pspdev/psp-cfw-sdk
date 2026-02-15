add_sdk_library(bootloadex)

target_sources(bootloadex PRIVATE
   crt0.S
	bootloadex.c
	scanner.c
	pspbtcnf.c
	patches_psp.c
	patches_vita.c
	bootloadex_ark.c
	patches_psp_ark.c
)

target_link_libraries(bootloadex PUBLIC iplsdk)
target_link_options(bootloadex INTERFACE -nostdlib -T${PROJECT_SOURCE_DIR}/build-tools/bootloadex.l)