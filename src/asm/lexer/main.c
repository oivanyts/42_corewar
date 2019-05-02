#include "asm.h"
#include "lexer.h"

int main()
{
	t_op_list	*op_list;

	op_list = get_op_list("bots/42.s");
	print_identifiers(op_list);
	return (0);
}