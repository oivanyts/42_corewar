#include "asm.h"
#include "lexer.h"
#include "disassembler.h"

int main()
{
	t_op_list	*op_list;

	op_list = get_op_list("bots/42.s");
	print_identifiers(op_list);
//	disassembler("bin/Car.cor");
	system("leaks -q asm");


	return (0);
}