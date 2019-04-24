cmake_minimum_required(VERSION 3.12)
project(corewar LANGUAGES C)
#set(CMAKE_C_COMPILER clang)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wextra -Werror")

add_subdirectory(./libft)

AUX_SOURCE_DIRECTORY(./src SOURCE_FILES)

add_executable(corewar ${SOURCE_FILES})

target_include_directories(corewar PUBLIC ./include)

target_link_libraries(corewar LIBFT)

