# add source and header files when compiling the given target.
# although it is not necessary to add header files, we also do that for easing the management of IDE.
target_sources(${CURRENT_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/float2Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/toTOA.c
        ${CMAKE_CURRENT_LIST_DIR}/toHeading2.c
        ${CMAKE_CURRENT_LIST_DIR}/toFloat.c
        ${CMAKE_CURRENT_LIST_DIR}/toUint24.c
        ${CMAKE_CURRENT_LIST_DIR}/target.h
        ${CMAKE_CURRENT_LIST_DIR}/toDist.c
        ${CMAKE_CURRENT_LIST_DIR}/charArray2Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/latLon2Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/nmea.c
        ${CMAKE_CURRENT_LIST_DIR}/toInt32.c
        ${CMAKE_CURRENT_LIST_DIR}/toDouble.c
        ${CMAKE_CURRENT_LIST_DIR}/toIcao.c
        ${CMAKE_CURRENT_LIST_DIR}/toLatLon.c
        ${CMAKE_CURRENT_LIST_DIR}/nmea.h
        ${CMAKE_CURRENT_LIST_DIR}/icao2Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/toGS.c
        ${CMAKE_CURRENT_LIST_DIR}/toVel.c
        ${CMAKE_CURRENT_LIST_DIR}/toUint16.c
        ${CMAKE_CURRENT_LIST_DIR}/sgUtil.h
        ${CMAKE_CURRENT_LIST_DIR}/toHeading.c
        ${CMAKE_CURRENT_LIST_DIR}/double2Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/uint242Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/uint322Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/int242Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/toUint32.c
        ${CMAKE_CURRENT_LIST_DIR}/calcChecksum.c
        ${CMAKE_CURRENT_LIST_DIR}/appendChecksum.c
        ${CMAKE_CURRENT_LIST_DIR}/target.c
        ${CMAKE_CURRENT_LIST_DIR}/uint162Buf.c
        ${CMAKE_CURRENT_LIST_DIR}/toInt16.c
        ${CMAKE_CURRENT_LIST_DIR}/toAlt.c
)

# add current directory to the compiler included directories when compiling the given target.
target_include_directories(${CURRENT_LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

