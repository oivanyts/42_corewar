/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:28:30 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/14 11:45:46 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_instrsize(struct s_token_list *tokenlist)
{
	int		size;
	t_op	*op;

	size = 0;
	while (tokenlist)
	{
		if (tokenlist->ident == INSTRUCTION)
		{
			op = ft_getfuncname(tokenlist);
			size = op->codoctal + 1;
		}
		else if (tokenlist->ident == REGISTER)
			size++;
		else if (tokenlist->ident == DIRECT || tokenlist->ident == DIRECT_LABEL)
			size += op->dirsize;
		else if (tokenlist->ident == INDIRECT ||
			tokenlist->ident == INDIRECT_LABEL)
			size += IND_SIZE;
		tokenlist = tokenlist->next;
	}
	return (size);
}

int		ft_getprogsize(t_op_list *oplist)
{
	int		instrstart;

	instrstart = 0;
	while (oplist)
	{
		oplist->instrstart = instrstart;
		oplist->instrsize = ft_instrsize(oplist->token_list);
		instrstart += oplist->instrsize;
		oplist = oplist->next;
	}
	return (instrstart);
}

void	ft_replacelable(t_op_list *oplist)
{
	t_op_list		*tmpoplist;
	t_token_list	*toklst;
	int				lable;

	tmpoplist = oplist;
	while (tmpoplist)
	{
		toklst = tmpoplist->token_list;
		while (toklst)
		{
			if (toklst->ident == INDIRECT_LABEL ||
				toklst->ident == DIRECT_LABEL)
			{
				lable = ft_searchlable(oplist, toklst) - tmpoplist->instrstart;
				free(toklst->data);
				toklst->data = ft_memalloc(sizeof(int));
				*((int *)toklst->data) = lable;
				toklst->ident = toklst->ident ==
						INDIRECT_LABEL ? INDIRECT : DIRECT;
			}
			toklst = toklst->next;
		}
		tmpoplist = tmpoplist->next;
	}
}

int		ft_searchlable(t_op_list *oplist, t_token_list *toklst)
{
	while (oplist)
	{
		if (oplist->token_list->ident == LABEL)
		{
			if (ft_strequ(toklst->data, oplist->token_list->data))
			{
				return (oplist->instrstart);
			}
		}
		oplist = oplist->next;
	}
	ft_errhandler(toklst);
	return (-1);
}
