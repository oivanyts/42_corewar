#include "disassembler.h"
#include "asm.h"

void	choose_arg(t_oper *oper, t_byte **bin, int i, t_dasm *dasm)
{
	if (oper->targs[i] == REG_CODE)
	{
		ft_fprintf(dasm->fd, "r%i", get_char_from_pointer(*bin));
		*bin += 1;
	}
	else if (oper->targs[i] == IND_CODE)
	{
		ft_fprintf(dasm->fd, "%i", get_short_from_pointer(*bin));
		*bin += IND_SIZE;
	}
	else
	{
		if (oper->op->some == 0)
		{
			ft_fprintf(dasm->fd, "%c%i", DIRECT_CHAR, get_int_from_pointer(*bin));
			*bin += REG_SIZE;
		}
		else
		{
			ft_fprintf(dasm->fd, "%c%i", DIRECT_CHAR, get_short_from_pointer(*bin));
			*bin += IND_SIZE;
		}
	}
}

void	do_operation(t_dasm *dasm, t_byte *bin)
{
	t_oper	oper;
	int 	i;

	oper.start = bin;
	oper.op = &g_op_tab[get_char_from_pointer(bin++) - 1];
	ft_fprintf(dasm->fd, "%s ", oper.op->name);
	if (oper.op->codoctal)
		get_type_arg(oper.targs, bin++);
	else
		oper.targs[0] = DIR_CODE;
	oper.separators = oper.op->args - 1;
	i = 0;
	while (i < oper.op->args)
	{
		choose_arg(&oper, &bin, i, dasm);
		if (oper.separators-- > 0)
			ft_fprintf(dasm->fd, "%c ", SEPARATOR_CHAR);
		i++;
	}
	ft_fprintf(dasm->fd, "\n");
	dasm->curr += bin - oper.start;
}