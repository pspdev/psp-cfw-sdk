project(sdktools VERSION 1.0)

file(GLOB_RECURSE SCRIPTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.py")

foreach(SCRIPT IN LISTS SCRIPTS)
   get_filename_component(FILE_WE ${SCRIPT} NAME_WE)
   get_filename_component(PARENT_DIR ${SCRIPT} DIRECTORY)
   get_filename_component(PARENT_NAME ${PARENT_DIR} NAME)

   if (PARENT_NAME STREQUAL "ipltools")
      set(TARGET_NAME "ipltool_${FILE_WE}")
   else()
      set(TARGET_NAME "tool_${FILE_WE}")
   endif()

   add_custom_target(${TARGET_NAME} ALL
      DEPENDS ${SCRIPT}
   )
   set_property(TARGET ${TARGET_NAME} PROPERTY EXEC ${SCRIPT})
endforeach()

function(create_raw_binary TARGET)
   add_custom_command(
      TARGET ${TARGET}
      POST_BUILD
      COMMAND psp-strip -s ${TARGET}
      COMMAND psp-objcopy -O binary ${TARGET} ${TARGET}.bin
   )
endfunction()