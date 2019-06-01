NAME_ASM = asm
NAME_VM = vm

FLAGS = -Wall -Wextra -Werror

SRCS_ASM =./src/asm/bcode.c\
          ./src/asm/filename.c\
          ./src/asm/lable.c\
          ./src/asm/main.c\
          ./src/asm/subfunctions.c\
          ./src/asm/validation.c\
          ./src/asm/disassembler/disassembler.c\
          ./src/asm/disassembler/do_operation.c\
          ./src/asm/disassembler/get_big_endian_num.c\
          ./src/asm/disassembler/get_header.c\
          ./src/asm/disassembler/get_type_arg.c\
          ./src/asm/disassembler/read_binary.c\
          ./src/asm/lexer/id_state/id_state0.c\
          ./src/asm/lexer/id_state/id_state1.c\
          ./src/asm/lexer/id_state/id_state2.c\
          ./src/asm/lexer/lex_condition/lex_condition0.c\
          ./src/asm/lexer/lex_condition/lex_condition1.c\
          ./src/asm/lexer/lex_condition/lex_condition2.c\
          ./src/asm/lexer/list_operations/op_list_operations.c\
          ./src/asm/lexer/list_operations/token_list_operations.c\
          ./src/asm/lexer/error.c\
          ./src/asm/lexer/finite_state_machine.c\
          ./src/asm/lexer/init_lexer.c\
          ./src/asm/lexer/lexer.c\
          ./src/asm/lexer/main.c\
          ./src/asm/lexer/read_text.c\
          ./src/asm/lexer/str_cmp.c

INC = ./include/abstract_cpu.h\
      ./include/array.h\
      ./include/asm.h\
      ./include/disassembler.h\
      ./include/error.h\
      ./include/errors.h\
      ./include/fsm.h\
      ./include/id_states.h\
      ./include/lex_conditions.h\
      ./include/lexer.h\
      ./include/op.h\
      ./include/opcalls.h\
      ./include/thread_array.h\
      ./include/utils.h\
      ./include/vm.h\
      ./include/vs.h

OBJ_ASM = $(SRCS_ASM:.c=.o)

all: libft $(NAME_ASM)

.PHONY : libft
libft:
	@make -C ./libft

$(NAME_ASM): $(OBJ_ASM) ./libft/libft.a
	@echo "Building of asm..."
	@gcc -o $(NAME_ASM) $(OBJ_ASM) ./libft/libft.a

%.o: %.c $(INC)
	gcc $(FLAGS) -I./include -I./libft/includes -o $@ -c $<

clean:
	@make clean -C ./libft
	@rm -f $(OBJ_ASM)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME_ASM)

re: fclean all

