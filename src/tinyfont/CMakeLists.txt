add_sdk_library(tinyfont STATIC)

target_sources(tinyfont PRIVATE
   tinyfont.c
   font.c
)

target_include_directories(tinyfont PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_custom_command(TARGET tinyfont POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${HEADER_FILES} "${SDK_INCLUDE_DIR}/"
	COMMENT "Copying $<TARGET_FILE_NAME:tinyfont> headers to include/"
)