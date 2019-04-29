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

int ft_listlen(t_token_list *toklst)
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

void 	ft_chekargs(t_token_list *lst, t_op *op)
{
	int i;
	int argnum;

	i = 1;
	argnum = 0;
	while (lst)
	{
		if (i > 1 && (i % 2) && lst->ident != SEPARATOR)
			exit(6);
		else if (i > 1 && !(i % 2) && !(ft_typearg(lst->ident) & op->targs[argnum++]))
			exit(9);
		lst = lst->next;
		i++;
	}
}

void	ft_validation (t_op_list *oplist)
{
	t_op *op;

	if (oplist->token_list->ident == NAME && oplist->next->token_list->ident == COMMENT)
		oplist = oplist->next->next;
	else if  (oplist->next->token_list->ident == NAME && oplist->token_list->ident == COMMENT)
		oplist = oplist->next->next;
	else
		exit(11);
	while (oplist)
	{
		if (!(op = ft_checkname(oplist->token_list)))
			exit(8);
		if (ft_listlen(oplist->token_list) != op->args * 2)
			exit(7);
		ft_chekargs(oplist->token_list, op);
		oplist = oplist->next;
	}
}