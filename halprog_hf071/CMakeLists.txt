cmake_minimum_required(VERSION 3.0.0)
project(halprog_071_thread VERSION 0.1.0)

include(CTest)
enable_testing()

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON
                                                 CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
                                               $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#if(BUILD_TESTING)
#  add_executable(test1 test1.cpp)
#  add_test(NAME test_op COMMAND test_op)
#endif(BUILD_TESTING)
                                               
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)