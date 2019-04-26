/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:47:27 by npiatiko          #+#    #+#             */
/*   Updated: 2019/04/26 15:42:26 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"



int		main(int argc, char **argv)
{
	t_token_list	*toklst;
	t_op_list *oplist;

	oplist = ft_memalloc(sizeof(t_op_list));
	toklst = ft_memalloc(sizeof(t_token_list));
	toklst->next = ft_memalloc(sizeof(t_token_list));
//	toklst->next->next = ft_memalloc(sizeof(t_token_list));
	toklst->data = "live";
	toklst->ident = INSTRUCTION;
	toklst->next->ident = DIRECT;
	toklst->next->data = "1";
//	toklst->next->next->ident = SEPARATOR;
//	toklst->next->next->data = ",";
	oplist->token_list = toklst;
	ft_validation (oplist);
	return (0);
}
