/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:20:05 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/07 15:20:07 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op		*ft_getfuncname(t_token_list *toklst)
{
	int		i;
	t_op	*op;

	i = -1;
	toklst->ident == LABEL ? toklst = toklst->next : 0;
	op = toklst ? NULL : &g_op_tab[16];
	if (toklst && toklst->ident == INSTRUCTION)
		while (++i < 16)
			ft_strequ(toklst->data, g_op_tab[i].name) ? op = &g_op_tab[i] : 0;
	if (!op)
		ft_errhandler(toklst);
	return (op);
}

void		ft_chekargs(t_token_list *toklst, t_op *op)
{
	int				i;
	int				argnum;
	t_token_list	*tmp;

	i = 1;
	argnum = 0;
	toklst->ident == LABEL ? toklst = toklst->next : 0;
	while (toklst)
	{
		if (i > op->args * 2)
			ft_errhandler(toklst);
		if (i > 1 && (i % 2) && toklst->ident != SEPARATOR)
			ft_errhandler(toklst);
		else if (i > 1 && !(i % 2) &&
		!(ft_gettypearg(toklst->ident) & op->targs[argnum++]))
			ft_errhandler(toklst);
		tmp = toklst;
		toklst = toklst->next;
		i++;
	}
	if (i <= op->args * 2)
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] %s\n",
				tmp->row, tmp->col + 1, "ENDLINE");
		ft_exit("Argument not found.", 16);
	}
}

void		ft_copystring(char *dst, t_token_list *src)
{
	if (ft_toklistlen(src) == 2)
	{
		if (src->next->ident == STRING)
		{
			if (ft_strlen(src->next->data) <= (src->ident == NAME ?
											PROG_NAME_LENGTH : COMMENT_LENGTH))
				ft_memcpy(dst, src->next->data, ft_strlen(src->next->data));
			else
			{
				ft_printf("Syntax error at token [TOKEN][%03d:%03d] %s\n",
				src->next->row, src->next->col, g_ident_str[src->next->ident]);
				ft_exit("String to long.", 16);
			}
		}
		else
			ft_errhandler(src->next);
	}
	else if (ft_toklistlen(src) > 2)
		ft_errhandler(src->next->next);
	else
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] %s\n",
				src->row, src->col + 1, "ENDLINE");
		ft_exit("String not found.", 16);
	}
}

void		ft_checkheader(t_op_list **oplist, t_header *header)
{
	if ((*oplist)->token_list->ident == NAME)
		if ((*oplist)->next->token_list->ident == COMMENT)
		{
			ft_copystring(header->prog_name, (*oplist)->token_list);
			ft_copystring(header->comment, (*oplist)->next->token_list);
		}
		else
			ft_errhandler((*oplist)->next->token_list);
	else if ((*oplist)->next->token_list->ident == NAME)
		if ((*oplist)->token_list->ident == COMMENT)
		{
			ft_copystring(header->comment, (*oplist)->token_list);
			ft_copystring(header->prog_name, (*oplist)->next->token_list);
		}
		else
			ft_errhandler((*oplist)->token_list);
	else
		ft_errhandler((*oplist)->next->token_list);
	*oplist = (*oplist)->next->next;
}

t_header	*ft_validation(t_op_list *oplist)
{
	t_op		*op;
	t_header	*header;
	t_op_list	*tmp;

	tmp = oplist;
	header = ft_memalloc(sizeof(t_header));
	ft_oplistlen(oplist) >= 2 ? 0 : ft_exit("File to short.", 13);
	ft_checkheader(&oplist, header);
	header->magic = COREWAR_EXEC_MAGIC;
	while (oplist)
	{
		op = ft_getfuncname(oplist->token_list);
		ft_chekargs(oplist->token_list, op);
		oplist = oplist->next;
	}
	header->prog_size = ft_getprogsize(tmp);
	ft_replacelable(tmp);
	return (header);
}
