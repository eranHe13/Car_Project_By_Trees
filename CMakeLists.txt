cmake_minimum_required(VERSION 3.19)
project(Car_Project_By_Trees C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic-errors -lm")
add_executable(Car_Project_By_Trees main.c Supplier.c Supplier.h)