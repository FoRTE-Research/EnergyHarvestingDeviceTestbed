cmake_minimum_required(VERSION 3.17)
project(aes_test C)

ADD_LIBRARY( aesLib STATIC
        gladman/aeskey.c gladman/aescrypt.c gladman/aestab.c gladman/aesaux.c gladman/aestst.c tiny_aes/aes.c)

set(CMAKE_C_STANDARD 99)

add_executable(aes_test main.c)

TARGET_LINK_LIBRARIES( aes_test
        aesLib )
