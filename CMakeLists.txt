cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
project(libbasen
    VERSION 1.1.1
    DESCRIPTION "c++20 encoding/decoding from arbitrary base"
    LANGUAGES CXX
)

set(CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-result -O3")

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
target_include_directories(basen PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)