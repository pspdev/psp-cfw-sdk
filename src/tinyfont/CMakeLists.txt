add_sdk_library(tinyfont STATIC)

target_sources(tinyfont PRIVATE
   tinyfont.c
   font.c
)

target_include_directories(tinyfont PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(TARGET tinyfont POST_BUILD
   COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/tinyfont.h" "${SDK_INCLUDE_DIR}/"
   COMMENT "Copying header file"
)