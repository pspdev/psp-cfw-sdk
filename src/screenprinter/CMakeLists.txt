add_library(screenprinter STATIC)

target_sources(screenprinter PRIVATE
   lib.c
   font.c
   screenprinter.c
)

target_compile_options(screenprinter PRIVATE -std=c99 -Wall -Os -G0 -fno-pic)
target_include_directories(screenprinter PUBLIC ${SDK_INCLUDE_DIR})
target_link_libraries(screenprinter PRIVATE colordebugger)

add_dependencies(screenprinter CopyPrebuiltSdkLibs)

add_custom_command(TARGET screenprinter POST_BUILD
   COMMAND cp "$<TARGET_FILE:screenprinter>" "${SDK_LIBS_DIR}/"
   COMMENT "Copying to libs folder"
)
