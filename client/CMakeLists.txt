cmake_minimum_required(VERSION 2.6)
project ( ChatApp )

set (CMAKE_CXX_STANDARD 11)

set ( SOURCES
 main.cpp
 mainwindow.cpp
 ServerConnection.cpp
 JSONHandler.cpp
 ClientServerInteraction.cpp
 GUIUpdater.cpp
 ResponseHandler.cpp
 ClientListHandler.cpp
 MessageHandler.cpp
)

set ( MOC_HEADERS
 mainwindow.h
 ClientServerInteraction.h
)

set ( UIS
 mainwindow.ui
)

#set ( RESOURCES
# main.qrc
#)

find_package(Boost 1.40.0 REQUIRED system thread serialization)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

# Next lines needed for building all Qt projects
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )


# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

# compile
add_executable( ChatApp ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
# or use line below instead, if you using Windows ™ Operating System.
#add_executable( ChatApp WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

link_directories(ChatApp ${Boost_LIBRARY_DIRS})

target_link_libraries( ChatApp ${QT_LIBRARIES} )
target_link_libraries( ChatApp ${GTEST_LIBRARIES} pthread)
target_link_libraries( ChatApp ${Boost_LIBRARIES})
target_link_libraries( ChatApp ${JSONCPP_LIBRARIES})


