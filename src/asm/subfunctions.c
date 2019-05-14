/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:16:43 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/14 14:37:47 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit(char *stre, int e)
{
	ft_printf("Error: %s\n", stre);
	e == 23 ? ft_printf("usage: asm [-d][filename]\n"
						"\t-d: disassemble *.cor to *.s.\n") : 0;
	system("leaks -q asm");
	exit(e);
}

void	ft_errhandler(t_token_list *toklst)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] %s\n",
			toklst->row, toklst->col, g_ident_str[toklst->ident]);
	system("leaks -q asm");
	exit(8);
}

int		ft_toklistlen(t_token_list *toklst)
{
	int i;

	i = 0;
	toklst->ident == LABEL ? toklst = toklst->next : 0;
	while (toklst->ident != ENDLINE)
	{
		i++;
		toklst = toklst->next;
	}
	return (i);
}

int		ft_oplistlen(t_op_list *oplist)
{
	int i;

	i = 0;
	while (oplist->next)
	{
		i++;
		oplist = oplist->next;
	}
	if (oplist->token_list->ident != END)
		ft_exit("Syntax error - unexpected end of input "
		"(Perhaps you forgot to end with a newline ?)\n", 78);
	return (i);
}

int		ft_gettypearg(t_identifier ident)
{
	if (ident == REGISTER)
		return (T_REG);
	else if (ident == INDIRECT || ident == INDIRECT_LABEL)
		return (T_IND);
	else if (ident == DIRECT || ident == DIRECT_LABEL)
		return (T_DIR);
	return (0);
}
