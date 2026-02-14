cmake_minimum_required(VERSION 3.16)

include(../build-tools/CreateStubLib.cmake)

function(add_sdk_library name)
   add_library(${name} STATIC)
  
   target_compile_options(${name} PRIVATE -std=c99 -Wall -Os -G0 -fno-pic)
   target_include_directories(${name} PUBLIC ${SDK_INCLUDE_DIR})

   add_dependencies(${name} CopyPrebuiltSdkLibs)

   add_custom_command(TARGET ${name} POST_BUILD
      COMMAND cp "$<TARGET_FILE:${name}>" "${SDK_LIBS_DIR}/"
      COMMENT "Copying $<TARGET_FILE_NAME:${LIB_NAME}> to libs/"
)
endfunction()

add_subdirectory(AdrenalineCtrl)
add_subdirectory(ArkCtrl)
add_subdirectory(DCManager)
add_subdirectory(KUBridge)
add_subdirectory(LibCisoRead)
add_subdirectory(LibPspExploit)
add_subdirectory(SystemCtrlForUser)
add_subdirectory(SystemCtrlForKernel)
add_subdirectory(VshCtrl)
add_subdirectory(SysclibForUser)
add_subdirectory(idsRegeneration)
add_subdirectory(idsRegeneration_driver)
add_subdirectory(isoCtrl_driver)
add_subdirectory(kpspident)
add_subdirectory(libintraFont_stub)
add_subdirectory(libpng_stub)
add_subdirectory(libpspav_stub)
add_subdirectory(libpspftp_stub)
add_subdirectory(microlz)
add_subdirectory(pspDecrypt)
add_subdirectory(pspIplUpdate)
add_subdirectory(pspKbootiUpdate)
add_subdirectory(pspPSAR)
add_subdirectory(guglue)
add_subdirectory(ansi-c)
add_subdirectory(colordebugger)
add_subdirectory(screenprinter)
add_subdirectory(mini2d)
add_subdirectory(iplsdk)
