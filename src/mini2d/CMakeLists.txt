add_library(mini2d STATIC)

target_sources(mini2d PRIVATE
   font.c
   graphics.c
)

target_compile_options(mini2d PRIVATE -std=c99 -Wall -Os -G0 -fno-pic)
target_include_directories(mini2d PUBLIC ${SDK_INCLUDE_DIR})

add_dependencies(mini2d CopyPrebuiltSdkLibs)

add_custom_command(TARGET mini2d POST_BUILD
   COMMAND cp "$<TARGET_FILE:mini2d>" "${SDK_LIBS_DIR}/"
   COMMENT "Copying to libs folder"
)
