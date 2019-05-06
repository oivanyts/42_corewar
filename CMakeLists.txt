cmake_minimum_required(VERSION 3.12)
project(corewar LANGUAGES C)
set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -O3")

add_subdirectory(./libft)

AUX_SOURCE_DIRECTORY(./src/vm/ SOURCE_FILES_VM)
AUX_SOURCE_DIRECTORY(./src/asm/ SOURCE_FILES_ASM)


add_executable(vm ${SOURCE_FILES_VM} src/vm/opcalls.c include/thread_array.h src/vm/thread_array.c include/error.h include/abstract_cpu.h src/vm/abstract_cpu.c include/utils.h)
add_executable(asm ${SOURCE_FILES_ASM} include/opcalls.h)

target_include_directories(vm PUBLIC ./include)
target_include_directories(asm PUBLIC ./include)

target_link_libraries(vm LIBFT)
target_link_libraries(asm LIBFT)
