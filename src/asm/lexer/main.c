//
// Created by Vladyslav USLYSTYI on 2019-04-25.
//

#include "asm.h"
#include "lexer.h"

int main()
{
	t_op_list	*op_list;

	op_list = get_op_list("bots/toto.s");
	print_identifiers(op_list);
	return (0);
}