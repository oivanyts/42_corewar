#include "asm.h"

void	err_lex(t_asm *a)
{
	ft_printf("Lexical error at [%i:%i]\n", a->fsm->st_row, a->fsm->st_col);
	exit(1);
}

void	err_no_endline(t_asm *a)
{
	ft_printf("Syntax error!\n");
	ft_printf("You forgot to put endline at the end of the row [%i].",
			a->fsm->st_row);
	exit(1);
}

void	err_no_closed_quote(t_asm *a)
{
	ft_printf("You have open quote at [%i:%i], but don't have closed quote.",
			  a->fsm->st_row, a->fsm->st_col);
	exit(1);
}

void	err_empty_file(t_asm *a)
{
	if (a)
		;
	ft_printf("The file hasn't any instruction.");
	exit(1);
}

