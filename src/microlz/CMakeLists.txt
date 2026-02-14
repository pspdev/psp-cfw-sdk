add_sdk_library(microlz)

target_sources(microlz PRIVATE
   lz4.c
   minilzo.c
)