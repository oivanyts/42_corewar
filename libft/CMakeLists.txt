cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_COMPILER clang)
#project(LIBFT LANGUAGES C)

# functions find all sourses in path and add their to target
AUX_SOURCE_DIRECTORY(./src LIB_SRCS)
# create library with sourses
add_library(LIBFT STATIC ${LIB_SRCS})
# Specify the foulder with headers for library (or executable)
target_include_directories(LIBFT PUBLIC ./includes)
# Specify compile options for library
#target_compile_options(LIBFT PRIVATE -Wall -Wextra -Werror)