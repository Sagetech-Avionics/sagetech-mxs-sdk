# add source and header files when compiling the given target.
# although it is not necessary to add header files, we also do that for easing the management of IDE.
target_sources(${CURRENT_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeStatus.c
        ${CMAKE_CURRENT_LIST_DIR}/sg.h
        ${CMAKE_CURRENT_LIST_DIR}/sgs.h
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeDataReq.c
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeInstall.c
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeGPS.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeSVR.c
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeOperating.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeInstall.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeHealthMonitor.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeMSR.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeVersion.c
        ${CMAKE_CURRENT_LIST_DIR}/sgsDecodeDF0.c
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeFlightId.c
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeTargetReq.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeSerialNumber.c
        ${CMAKE_CURRENT_LIST_DIR}/sgg.h
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeFlightId.c
        ${CMAKE_CURRENT_LIST_DIR}/sgEncodeMode.c
        ${CMAKE_CURRENT_LIST_DIR}/sgDecodeAck.c
)

# add current directory to the compiler included directories when compiling the given target.
target_include_directories(${CURRENT_LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

