cmake_minimum_required(VERSION 3.0.0)
project(halprog_hf051_mat VERSION 0.1.0)

include(CTest)
enable_testing()

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)

add_executable(halprog_hf051_mat main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON
                                                 CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
                                               $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)
if(BUILD_TESTING)
  add_executable(test_op_add test_op_add.cpp)
  add_test(NAME test_op_add COMMAND test_op_add)

  add_executable(test_op_sub test_op_sub.cpp)
  add_test(NAME test_op_sub COMMAND test_op_sub)

  add_executable(test_op_mulscl test_op_mulscl.cpp)
  add_test(NAME test_op_mulscl COMMAND test_op_mulscl)

  add_executable(test_op_divscl test_op_divscl.cpp)
  add_test(NAME test_op_divscl COMMAND test_op_divscl)

  add_executable(test_op_mulmat test_op_mulmat.cpp)
  add_test(NAME test_op_mulmat COMMAND test_op_mulmat)

  add_executable(test_op_assigned test_op_assigned.cpp)
  add_test(NAME test_op_assigned COMMAND test_op_assigned)

  add_executable(test_co test_co.cpp)
  add_test(NAME test_co COMMAND test_co)

  add_executable(test_assigned test_assigned.cpp)
  add_test(NAME test_assigned COMMAND test_assigned)

  add_executable(test_stream test_stream.cpp)
  add_test(NAME test_stream COMMAND test_stream)
endif(BUILD_TESTING)
                                               
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
