add_sdk_library(bootloadex)

target_sources(bootloadex PRIVATE
	crt0.S
	scanner.c
	pspbtcnf.c
	vitaflash.c
	bootloadex.c
	patches_psp.c
	patches_vita.c
	bootloadex_ark.c
	bootloadex_lme.c
	patches_psp_ark.c
	patches_psp_pro.c
	patches_psp_lme.c
	patches_psp_m33.c
)

target_link_libraries(bootloadex PUBLIC iplsdk)
target_link_options(bootloadex INTERFACE -nostdlib -T${PROJECT_SOURCE_DIR}/build-tools/bootloadex.l)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_custom_command(TARGET bootloadex POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${HEADER_FILES} "${SDK_INCLUDE_DIR}/"
	COMMENT "Copying $<TARGET_FILE_NAME:bootloadex> headers to include/"
)