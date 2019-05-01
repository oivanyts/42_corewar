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

void	ft_write(int fd, void *data, size_t size)
{
	while (size--)
	{
		write(fd, &data[size], 1);
	}
}

void	ft_writehead(int fd, t_header *header)
{
	ft_write(fd, &header->magic, 4);
	write(fd, header->prog_name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	ft_write(fd, &header->prog_size, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
}

int		main(int argc, char **argv)
{
	t_token_list	*toklst;
	t_op_list *oplist;
	int fd;
	t_header *header;

	header = ft_memalloc(sizeof(t_header));
	oplist = ft_memalloc(sizeof(t_op_list));
	oplist->next = ft_memalloc(sizeof(t_op_list));
	oplist->next->next = ft_memalloc(sizeof(t_op_list));
	toklst = ft_memalloc(sizeof(t_token_list));
	toklst->next = ft_memalloc(sizeof(t_token_list));
	toklst->next->next = ft_memalloc(sizeof(t_token_list));
	toklst->next->next->next = ft_memalloc(sizeof(t_token_list));
	oplist->token_list = ft_memalloc(sizeof(t_token_list));
	oplist->token_list->next = ft_memalloc(sizeof(t_token_list));
	oplist->next->token_list = ft_memalloc(sizeof(t_token_list));
	oplist->next->token_list->next = ft_memalloc(sizeof(t_token_list));
	oplist->token_list->ident = NAME;
	oplist->token_list->next->ident = STRING;
	oplist->token_list->next->data = "champna";
	oplist->next->token_list->ident = COMMENT;
	oplist->next->token_list->next->ident = STRING;
	oplist->next->token_list->next->data = "champcoment";
	toklst->data = "st";
	toklst->ident = INSTRUCTION;
	toklst->next->ident = REGISTER;
	toklst->next->data = "1";
	toklst->next->next->ident = SEPARATOR;
	toklst->next->next->data = ",";
	toklst->next->next->next->ident = REGISTER;
	toklst->next->next->next->data = "43";
	oplist->next->next->token_list = toklst;
	ft_validation(oplist, header);
	fd = open("test", O_RDWR | O_CREAT | O_TRUNC, 0777);
	ft_writehead(fd, header);
	close(fd);
	return (0);
}

