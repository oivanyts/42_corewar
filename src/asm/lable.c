/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:28:30 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/07 13:42:48 by npiatiko         ###   ########.fr       */
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
	char			*tmpdata;

	tmpoplist = oplist;
	while (tmpoplist)
	{
		toklst = tmpoplist->token_list;
		while (toklst)
		{
			if (toklst->ident == INDIRECT_LABEL ||
				toklst->ident == DIRECT_LABEL)
			{
				toklst->ident = toklst->ident ==
						INDIRECT_LABEL ? INDIRECT : DIRECT;
				tmpdata = toklst->data;
				toklst->data = ft_memalloc(4);
				*((int *)(toklst->data)) =
						ft_searchlable(oplist, tmpdata) - tmpoplist->instrstart;
				free(tmpdata);
			}
			toklst = toklst->next;
		}
		tmpoplist = tmpoplist->next;
	}
}

int		ft_searchlable(t_op_list *oplist, char *data)
{
	while (oplist)
	{
		if (oplist->token_list->ident == LABEL)
		{
			if (ft_strequ(data, oplist->token_list->data))
			{
				return (oplist->instrstart);
			}
		}
		oplist = oplist->next;
	}
	ft_exit("Unknown lable.", 111);
	return (-1);
}
