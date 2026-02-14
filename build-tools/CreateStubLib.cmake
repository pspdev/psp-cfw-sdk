function(add_stub_lib LIB_NAME SRC_FILE DEFINE_PREFIX)

   add_library(${LIB_NAME} STATIC)

   target_compile_options(${LIB_NAME} PRIVATE -std=c99 -Os -G0 -Wall -fno-builtin-printf)
   target_include_directories(${LIB_NAME} PUBLIC ${SDK_INCLUDE_DIR})

   get_filename_component(SRC_ABS "${SRC_FILE}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

   file(READ "${SRC_ABS}" SRC_CONTENT)
   string(REGEX MATCHALL "IMPORT_FUNC" MATCHES "${SRC_CONTENT}")
   list(LENGTH MATCHES NUM_STUBS)

   foreach(i RANGE 0 ${NUM_STUBS})
      math(EXPR PaddedNum "10000 + ${i}")
      string(SUBSTRING "${PaddedNum}" 1 4 PaddedNum)
      set(STUB_DEFINE "F_${DEFINE_PREFIX}_${PaddedNum}")
      set(STUB_FILE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_${PaddedNum}.S")

      add_custom_command(
         OUTPUT "${STUB_FILE}"
         COMMAND cp ${SRC_ABS} ${STUB_FILE} 
         DEPENDS ${SRC_FILE}
      )

      target_sources(${LIB_NAME} PRIVATE ${STUB_FILE})
      set_source_files_properties(${STUB_FILE} PROPERTIES COMPILE_DEFINITIONS ${STUB_DEFINE})
   endforeach()

   add_dependencies(${LIB_NAME} CopyPrebuiltSdkLibs)

   add_custom_command(TARGET ${LIB_NAME} POST_BUILD
      COMMAND cp "$<TARGET_FILE:${LIB_NAME}>" "${SDK_LIBS_DIR}/"
      COMMENT "Copying $<TARGET_FILE_NAME:${LIB_NAME}> to libs/"
   )
endfunction()
