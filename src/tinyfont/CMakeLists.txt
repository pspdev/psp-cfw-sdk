add_sdk_library(tinyfont STATIC)

target_sources(tinyfont PRIVATE
   tinyfont.c
   font.c
)

target_include_directories(tinyfont PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}
)
