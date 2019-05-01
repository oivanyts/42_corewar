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
#include "lexer.h"

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
	t_op_list *oplist;
	int fd;
	t_header *header;

	header = ft_memalloc(sizeof(t_header));
	oplist = get_op_list("vm_champs/champs/ex.s");
	print_identifiers(oplist);
	ft_printf("\n\n\n");
	ft_validation(oplist, header);
	ft_printf("%hx", -19);
//	if ((fd = open("test", O_RDWR | O_CREAT | O_TRUNC, 0755)) < 0)
//		ft_exit(strerror(errno), errno);
//	ft_writehead(fd, header);
//	close(fd);
	return (0);
}

