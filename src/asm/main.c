/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:47:27 by npiatiko          #+#    #+#             */
/*   Updated: 2019/04/26 19:02:11 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char **argv)
{
	t_token_list	*toklst;
	t_op_list *oplist;

	oplist = ft_memalloc(sizeof(t_op_list));
	oplist->next = ft_memalloc(sizeof(t_op_list));
	oplist->next->next = ft_memalloc(sizeof(t_op_list));
	toklst = ft_memalloc(sizeof(t_token_list));
	toklst->next = ft_memalloc(sizeof(t_token_list));
//	toklst->next->next = ft_memalloc(sizeof(t_token_list));
//	toklst->next->next->next = ft_memalloc(sizeof(t_token_list));
	oplist->token_list = ft_memalloc(sizeof(t_token_list));
	oplist->next->token_list = ft_memalloc(sizeof(t_token_list));
	oplist->token_list->ident = NAME;
	oplist->next->token_list->ident = COMMENT;
	toklst->data = "aff";
	toklst->ident = INSTRUCTION;
	toklst->next->ident = REGISTER;
	toklst->next->data = "1";
//	toklst->next->next->ident = SEPARATOR;
//	toklst->next->next->data = ",";
//	toklst->next->next->next->ident = REGISTER;
//	toklst->next->next->next->data = "43";
	oplist->next->next->token_list = toklst;
	ft_validation (oplist);
	return (0);
}

