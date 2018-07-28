cmake_minimum_required(VERSION 2.8)
set(MODULE_NAME UnitTests)

set (CMAKE_CXX_STANDARD 11)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../ChatAppServer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(SOURCE_EXE tests.cpp  ../ChatAppServer/HistoryManager.cpp ../ChatAppServer/ChatHistory.cpp ../ChatAppServer/RequestHandler.cpp ../ChatAppServer/GetMessageHandler.cpp ../ChatAppServer/SaveMessageHandler.cpp ../ChatAppServer/ClientListHandler.cpp)

add_executable(${MODULE_NAME} ${SOURCE_EXE})

target_link_libraries(${MODULE_NAME} ${GTEST_LIBRARIES} ${JSONCPP_LIBRARIES} pthread)

