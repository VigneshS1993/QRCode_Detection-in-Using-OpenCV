cmake_minimum_required(VERSION 2.8)

project(CamController)

find_package( OpenCV REQUIRED )
if( OpenCV_FOUND )
list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )

set(DAEBOT_PD_SOURCE ${CMAKE_SOURCE_DIR}/DAEbot-PD)

include_directories( APPEND
    ${CMAKE_SOURCE_DIR}
    publisher/include
    ${DAEBOT_PD_SOURCE}
    /home/pi/DAEbot/Peripheral-Drivers/DAEbot-PD)

add_executable(${PROJECT_NAME}
    ../ControllerAreaNetwork/ControllerAreaNetwork.c
    global.h
    locationpublisherservice.h
    locationpublisherservice.cpp
    camcontrollermanager.h
    camcontrollermanager.cpp
    qrscanner.h
    qrscanner.cpp
    main.cpp)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/publisher/lib/libPublisher.a
    pthread
    ${OpenCV_LIBS}
    zbar
    )
