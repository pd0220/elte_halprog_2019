cmake_minimum_required(VERSION 3.0.0)
project(halprog_hf041_vec VERSION 0.1.0)

include(CTest)
enable_testing()

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)

add_executable(halprog_hf041_vec main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON
                                                 CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
                                               $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)
if(BUILD_TESTING)
  add_executable(test_op test_op.cpp)
  add_test(NAME test_op COMMAND test_op)

  add_executable(test_func test_func.cpp)
  add_test(NAME test_func COMMAND test_func)

  add_executable(test_stream test_stream.cpp)
  add_test(NAME test_stream COMMAND test_stream)
endif(BUILD_TESTING)
                                               
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)