add_stub_lib(pspav_stub libpspav.S libpspav 5)

target_include_directories(pspav_stub PUBLIC ${SDK_INCLUDE_DIR})