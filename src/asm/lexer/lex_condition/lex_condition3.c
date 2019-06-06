#include "lex_conditions.h"
#include "asm.h"
#include "lexer.h"

int 	lex_instruction(char *c, char st)
{
	static char	states[] = {1};
	int			i;

	if (at_right_state(states, sizeof(states), st))
	{
		i = -1;
		while (g_op_tab[++i].name)
			if (str_cmp(c, g_op_tab[i].name))
				return (1);
	}
	return (0);
}