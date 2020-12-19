cmake_minimum_required(VERSION 3.15...3.19)

option(CMAKE_EXPORT_COMPILE_COMMANDS "create compile_commands.json" ON)

project(cert-test LANGUAGES CXX VERSION 0.1.7)

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
    HINTS /usr/local/opt/llvm/bin/ /usr/local/bin /usr/bin
)
if(CLANG_TIDY)
    message(STATUS "set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

#----------------------------------------------------------
enable_testing()
#----------------------------------------------------------
file(GLOB TESTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} cert-*.cpp)

# Build all of the non-special tests
foreach(TEST_SOURCE ${TESTS})

    string(REPLACE ".cpp" "" TEST_TARGET "${TEST_SOURCE}")
    set(TEST_TARGET "test_${TEST_TARGET}")

    add_executable(${TEST_TARGET} ${TEST_SOURCE})
    target_compile_features(${TEST_TARGET} PRIVATE cxx_std_17)
    target_link_libraries(${TEST_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/library.a)
    add_test(NAME "${TEST_TARGET}" COMMAND "${TEST_TARGET}")

endforeach()


# ===================  build dependencies  ===================
include(FetchContent)
# ============================================================

find_package(CEREAL CONFIG)
if(NOT TARGET cereal::cereal)
   message(WARNING "Try to get cereal with FetchContent ...")
   fetchcontent_declare(
       cereal
       GIT_REPOSITORY git@github.com:ClausKlein/cereal.git
   )
   fetchcontent_makeavailable(cereal)
endif()

find_package(FMT CONFIG)
if(NOT TARGET fmt::fmt)
   message(WARNING "Try to get fmt with FetchContent ...")
   fetchcontent_declare(
       fmt
       GIT_REPOSITORY git@github.com:ClausKlein/fmt.git
   )
   fetchcontent_makeavailable(fmt)
endif()

find_package(SPAN CONFIG)
if(NOT TARGET tcb::span)
   message(WARNING "Try to get span with FetchContent ...")
   fetchcontent_declare(
       span
       GIT_REPOSITORY git@github.com:ClausKlein/span.git
   )
   fetchcontent_makeavailable(span)
endif()

find_package(Boost CONFIG)
#
# ============================================================
#

if(TARGET Boost::headers)
    add_executable(to_string to_string.cpp)
    target_link_libraries(to_string fmt::fmt Boost::headers)
endif()


add_executable(cereal-test cereal-test.cpp)
target_link_libraries(cereal-test cereal::cereal)

add_executable(dynamic_pointer_cast dynamic_pointer_cast.cpp)
target_compile_features(dynamic_pointer_cast PRIVATE cxx_std_17)

add_executable(slice slice.cpp)
target_compile_features(slice PRIVATE cxx_std_17)

add_executable(lookAndSay lookAndSay.cpp)
target_compile_features(lookAndSay PRIVATE cxx_std_17)


if(NOT CMAKE_CXX_STANDARD STREQUAL 17)
    add_executable(slide slide.cpp)
    target_compile_features(slide PRIVATE cxx_std_20)

    add_executable(safeComparison safeComparison.cpp)
    target_compile_features(safeComparison PRIVATE cxx_std_20)

    add_executable(timeConversion timeConversion.cpp)
    target_compile_features(timeConversion PRIVATE cxx_std_20)
else()
    add_executable(slide slide.cpp)
    target_link_libraries(slide tcb::span)
endif()

