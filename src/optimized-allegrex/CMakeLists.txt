option(BUILD_ALL "Include all optimized Allegrex routines" OFF)

add_sdk_library(optimized_allegrex STATIC)

target_sources(optimized_allegrex PRIVATE
    src/__ashldi3.S
    src/__ashrdi3.S
    src/__bitops.S
    src/__bswap.S
    src/__cmpdi2.S
    src/__divmoddi4.S
    src/__lshrdi3.S
    src/__muldi3.S
)


if(BUILD_ALL)
    target_sources(optimized_allegrex PRIVATE src/__udivmoddi4.S)
endif()

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_custom_command(TARGET optimized_allegrex POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${HEADER_FILES} "${SDK_INCLUDE_DIR}/"
	COMMENT "Copying $<TARGET_FILE_NAME:optimized_allegrex> headers to include/"
)