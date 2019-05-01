/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:37:25 by npiatiko          #+#    #+#             */
/*   Updated: 2019/04/26 18:31:35 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit(char *stre, int e)
{
	ft_printf("Error: %s\n", stre);
	exit(e);
}

int		ft_toklistlen(t_token_list *toklst)
{
	int i;

	i = 0;
	toklst->ident == LABEL ? toklst = toklst->next : 0;
	while (toklst)
	{
		i++;
		toklst = toklst->next;
	}
	return i;
}

int		ft_oplistlen(t_op_list *oplist)
{
	int i;

	i = 0;
	while (oplist)
	{
		i++;
		oplist = oplist->next;
	}
	return (i);
}

t_op	*ft_checkname(t_token_list *toklst)
{
	int i;
	t_op *op;

	i = -1;
	toklst->ident == LABEL ? toklst = toklst->next : 0;
	op = toklst ? NULL : &g_op_tab[16];
	if (toklst && toklst->ident == INSTRUCTION)
		while (++i < 16)
			ft_strequ(toklst->data, g_op_tab[i].name) ? op = &g_op_tab[i] : 0;
	return (op);
}

int		ft_typearg(t_identifier ident)
{
	if (ident == REGISTER)
		return (T_REG);
	else if (ident == INDIRECT || ident == INDIRECT_LABEL)
		return (T_IND);
	else if (ident == DIRECT || ident == DIRECT_LABEL)
		return (T_DIR);
	return (0);
}

void 	ft_chekargs(t_token_list *toklst, t_op *op)
{
	int i;
	int argnum;

	i = 1;
	argnum = 0;
	toklst->ident == LABEL ? toklst = toklst->next : 0;
	while (toklst)
	{
		if (i > 1 && (i % 2) && toklst->ident != SEPARATOR)
			ft_exit("Error format of arguments.", 6);
		else if (i > 1 && !(i % 2) && !(ft_typearg(toklst->ident) & op->targs[argnum++]))
			ft_exit("Wrong type of argument.", 9);
		toklst = toklst->next;
		i++;
	}
}

void	ft_copystring(char *dst, t_token_list *src)
{
	if (ft_toklistlen(src) == 2)
	{
		if (src->next->ident == STRING)
		{
			if (ft_strlen(src->next->data) <= (src->ident == NAME ?
			PROG_NAME_LENGTH : COMMENT_LENGTH))
			{
				ft_memcpy(dst, src->next->data, ft_strlen(src->next->data));
			}
			else
				ft_exit("String to long.", 16);
		}
		else
			ft_exit("String not found.", 17);
	}
	else
		ft_exit("Wrong format of file.", 18);
}

void	ft_checkheader(t_op_list **oplist, t_header *header)
{
	if ((*oplist)->token_list->ident == NAME)
		if ((*oplist)->next->token_list->ident == COMMENT)
		{
			ft_copystring(header->prog_name, (*oplist)->token_list);
			ft_copystring(header->comment, (*oplist)->next->token_list);
		}
		else
			ft_exit(".comment not found", 14);
	else if  ((*oplist)->next->token_list->ident == NAME)
		if ((*oplist)->token_list->ident == COMMENT)
		{
			ft_copystring(header->comment, (*oplist)->token_list);
			ft_copystring(header->prog_name, (*oplist)->next->token_list);
		}
		else
			ft_exit(".comment not found", 14);
	else
		ft_exit(".name not found", 15);
	*oplist = (*oplist)->next->next;
}

void	ft_validation(t_op_list *oplist, t_header *header)
{
	t_op *op;

	ft_oplistlen(oplist) > 2 ? 0 : ft_exit("File to short.", 13);
	ft_checkheader(&oplist, header);
	header->magic = COREWAR_EXEC_MAGIC;
	while (oplist)
	{
		if (!(op = ft_checkname(oplist->token_list)))
			ft_exit("Unknown instruction", 8);
		if (ft_toklistlen(oplist->token_list) != op->args * 2)
			ft_exit("Error number of arguments.", 7);
		ft_chekargs(oplist->token_list, op);
		oplist = oplist->next;
	}
}