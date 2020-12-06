cmake_minimum_required(VERSION 3.8...3.15)

option(CMAKE_EXPORT_COMPILE_COMMANDS "create compile_commands.json" ON)

project(cert-test LANGUAGES CXX VERSION 0.1.3)

#----------------------------------------------------------
# Compiler config
#----------------------------------------------------------
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast)
option(WITH_WERROR "Compile with '-Werror' C++ compiler flag" OFF)
if(WITH_WERROR)
    add_compile_options(-Werror)
endif()

find_program(CLANG_TIDY
    NAMES clang-tidy clang-tidy-7 clang-tidy-8 clang-tidy-9 clang-tidy-10 clang-tidy-11 clang-tidy-12
    HINTS /usr/local/bin /usr/bin
)
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

#----------------------------------------------------------
enable_testing()
#----------------------------------------------------------
set(SPECIAL_TESTS "cereal-test.cpp")
file(GLOB TESTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} cert-*.cpp)

# Build all of the non-special tests
foreach(TEST_SOURCE ${TESTS})
  # Check to see if our target is listed in "SPECIAL_TESTS"
  list(FIND SPECIAL_TESTS "${TEST_SOURCE}" IS_SPECIAL_TEST)

  if(IS_SPECIAL_TEST EQUAL -1)

    string(REPLACE ".cpp" "" TEST_TARGET "${TEST_SOURCE}")
    set(TEST_TARGET "test_${TEST_TARGET}")

    add_executable(${TEST_TARGET} ${TEST_SOURCE})
    target_compile_features(${TEST_TARGET} INTERFACE cxx_std_14)
    # target_link_libraries(${TEST_TARGET} ${LIBS})
    add_test(NAME "${TEST_TARGET}" COMMAND "${TEST_TARGET}")

  endif()

endforeach()

