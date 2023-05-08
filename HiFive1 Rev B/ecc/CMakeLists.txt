cmake_minimum_required(VERSION 3.17)
project(ecc_test C)

ADD_LIBRARY( eccLib STATIC
        bsd/uECC.c tiny_ecc/ecdh.c)

set(CMAKE_C_STANDARD 99)

add_executable(ecc_test main.c)

TARGET_LINK_LIBRARIES( ecc_test
        eccLib )
