add_sdk_library(screenprinter STATIC)

target_sources(screenprinter PRIVATE
   lib.c
   font.c
   screenprinter.c
)

target_link_libraries(screenprinter PRIVATE colordebugger)
