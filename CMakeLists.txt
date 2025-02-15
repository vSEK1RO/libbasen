cmake_minimum_required(VERSION 3.21)
project(libbasen
    VERSION 1.1.1
    DESCRIPTION "c++20 encoding/decoding from arbitrary base"
    LANGUAGES CXX
)

if(DEFINED BASEN_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${BASEN_SHARED_LIBS})
endif()

set(OBJS
    base58
    base64
    baseN
    hex
    Exception
    hash/sha256
)
set(SRCS)
foreach(OBJ ${OBJS})
    list(APPEND SRCS "src/${OBJ}.cpp")
endforeach()

add_library(basen ${SRCS})
add_library(basen::basen ALIAS basen)

target_compile_options(basen PRIVATE
    -std=c++20
    -Wall
    -Wextra
    -Werror
    -Wno-unused-result
    -O3
)
target_include_directories(basen PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)