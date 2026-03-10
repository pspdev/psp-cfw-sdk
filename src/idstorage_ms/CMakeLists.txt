add_sdk_library(idstorage_ms)

target_sources(idstorage_ms PRIVATE
   idstorage_ms.c
)

target_link_libraries(idstorage_ms PRIVATE ansic iplsdk)