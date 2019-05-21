cmake_minimum_required(VERSION 3.12)
project(corewar LANGUAGES C)
set(CMAKE_C_COMPILER clang)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-lncurses")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
add_subdirectory(./libft)

AUX_SOURCE_DIRECTORY(./src/vm/ SOURCE_FILES_VM)
AUX_SOURCE_DIRECTORY(./src/asm/ SOURCE_FILES_ASM)
AUX_SOURCE_DIRECTORY(./src/asm/disassembler SOURCE_FILES_ASM)
AUX_SOURCE_DIRECTORY(./src/asm/disassembler SOURCE_FILES_ASM)
AUX_SOURCE_DIRECTORY(src/vm/vs SOURCE_FILES_VS)



#file(GLOB_RECURSE ASM_SRC src/asm/ *.c)
add_executable(vm ${SOURCE_FILES_VM})
add_executable(vs ${SOURCE_FILES_VS})
add_executable(asm ${SOURCE_FILES_ASM} src/asm/lexer/lexer.c src/asm/lexer/read_text.c include/lexer.h src/asm/lexer/read_table_from.c src/asm/lexer/lex_condition/lex_condition0.c src/asm/lexer/lex_condition/lex_condition1.c src/asm/lexer/lex_condition/lex_condition2.c src/asm/lexer/id_state/id_state0.c src/asm/lexer/list_operations/op_list_operations.c src/asm/lexer/list_operations/token_list_operations.c src/asm/lexer/list_operations/label_list_operations.c src/asm/lexer/id_state/id_state1.c src/asm/lexer/id_state/id_state2.c include/lex_conditions.h include/id_states.h src/asm/lexer/finite_state_machine.c src/asm/lexer/str_cmp.c src/asm/lexer/init_lexer.c src/asm/lexer/error.c include/errors.h include/disassembler.h src/asm/disassembler/read_binary.c)
#add_executable(asm ${ASM_SRC})

target_include_directories(vm PUBLIC ./include)
target_include_directories(asm PUBLIC ./include)
target_include_directories(vs PUBLIC ./include)

target_link_libraries(vs LIBFT)
target_link_libraries(vm LIBFT)
target_link_libraries(asm LIBFT)
