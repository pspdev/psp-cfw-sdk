add_library(colordebugger STATIC)

target_sources(colordebugger PRIVATE
   colordebugger.c
)

target_compile_options(colordebugger PRIVATE -std=c99 -Wall -Os -G0 -fno-pic)
target_include_directories(colordebugger PUBLIC ${SDK_INCLUDE_DIR})

add_dependencies(colordebugger CopyPrebuiltSdkLibs)

add_custom_command(TARGET colordebugger POST_BUILD
   COMMAND cp "$<TARGET_FILE:colordebugger>" "${SDK_LIBS_DIR}/"
   COMMENT "Copying to libs folder"
)
