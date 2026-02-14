cmake_minimum_required(VERSION 3.16)

project(pspcfwsdk VERSION 1.0 LANGUAGES C ASM)

set(SDK_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(SDK_LIBS_DIR "${CMAKE_CURRENT_LIST_DIR}/libs")
set(STAMP_FILE "${SDK_LIBS_DIR}/.copied.stamp")

add_custom_command(
    OUTPUT ${STAMP_FILE}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/src/pre-built" "${SDK_LIBS_DIR}"
    COMMAND ${CMAKE_COMMAND} -E touch "${STAMP_FILE}"
    COMMENT "Copying pre-built files"
)

add_custom_target(CopyPrebuiltSdkLibs ALL
    DEPENDS ${STAMP_FILE}
)

add_subdirectory(src)
add_subdirectory(build-tools)