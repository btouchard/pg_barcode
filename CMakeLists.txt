cmake_minimum_required(VERSION 3.29)
project(pg_barcode C)

set(CMAKE_C_STANDARD 11)

add_executable(pg_barcode main.c
        src/datamatrix.c
        src/qrcode.c
        include/datamatrix.h
        include/qrcode.h)
