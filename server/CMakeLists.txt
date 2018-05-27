project(Server)
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

# Create a list with all .cpp source files
set( project_sources
   main.cpp
   ChatHistory.cpp
   ClientController.cpp
   Connection.cpp
   RequestHandler.cpp
)

find_package(Boost 1.40.0 REQUIRED system thread serialization)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

add_executable(Server ${project_sources})

link_directories(Server ${Boost_LIBRARY_DIRS})

target_link_libraries(Server ${GTEST_LIBRARIES} pthread)
target_link_libraries(Server ${Boost_LIBRARIES})
target_link_libraries(Server ${JSONCPP_LIBRARIES})





