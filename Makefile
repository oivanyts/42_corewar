NAME_ASM = asm
NAME_VM = corewar

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
          ./src/asm/lexer/read_text.c\
          ./src/asm/lexer/str_cmp.c

SRCS_VM = 	./src/vm/abstract_cpu.c\
            ./src/vm/abstract_cpu1.c\
            ./src/vm/abstract_cpu2.c\
            ./src/vm/array.c\
            ./src/vm/array_find.c\
            ./src/vm/array_insert.c\
            ./src/vm/array_size.c\
            ./src/vm/decode.c\
            ./src/vm/decode_param.c\
            ./src/vm/get_force_param_type.c\
            ./src/vm/get_options.c\
            ./src/vm/get_param_type.c\
            ./src/vm/handle_error.c\
            ./src/vm/load_from_file.c\
            ./src/vm/main.c\
            ./src/vm/op.c\
            ./src/vm/opcalls.c\
            ./src/vm/opcalls1.c\
            ./src/vm/opcalls2.c\
            ./src/vm/opcalls3.c\
            ./src/vm/opcalls4.c\
            ./src/vm/thread_array.c\
            ./src/vm/utils.c\
            ./src/vm/utils2.c\
            ./src/vm/vm.c\
            ./src/vm/vm_cycle.c\
            ./src/vm/vs/print_info.c\
            ./src/vm/vs/print_memory.c\
            ./src/vm/vs/sub_fns.c\
            ./src/vm/vs/vs_init.c

INC_GENERAL =./include/op.h

INC_ASM =	./include/asm.h\
			./include/disassembler.h\
			./include/errors.h\
			./include/fsm.h\
			./include/id_states.h\
			./include/lex_conditions.h\
			./include/lexer.h

INC_VM =	./include/abstract_cpu.h\
			./include/array.h\
			./include/error.h\
			./include/opcalls.h\
			./include/thread_array.h\
			./include/utils.h\
			./include/vm.h\
			./include/vs.h



OBJ_ASM = $(SRCS_ASM:.c=.o)

OBJ_VM = $(SRCS_VM:.c=.o)

all: libft $(NAME_ASM) $(NAME_VM)

.PHONY : libft
libft:
	make -C ./libft

$(NAME_ASM): $(OBJ_ASM) ./libft/libft.a
	@echo "Building of asm..."
	@gcc -o $(NAME_ASM) $(OBJ_ASM) ./libft/libft.a

$(NAME_VM): $(OBJ_VM) ./libft/libft.a
	@echo "Building of vm..."
	@gcc -o $(NAME_VM) $(OBJ_VM) ./libft/libft.a -lncurses

./src/asm/%.o: ./src/asm/%.c $(INC_ASM) $(INC_GENERAL)
	gcc $(FLAGS) -I./include -I./libft/includes -o $@ -c $<

./src/vm/%.o: ./src/vm/%.c $(INC_VM) $(INC_GENERAL)
	gcc $(FLAGS) -I./include -I./libft/includes -o $@ -c $<

clean:
	make clean -C ./libft
	rm -f $(OBJ_ASM)
	rm -f $(OBJ_VM)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME_ASM)
	rm -f $(NAME_VM)

re: fclean all

