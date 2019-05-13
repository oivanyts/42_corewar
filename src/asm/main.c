/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:47:27 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/13 15:26:19 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lexer.h"

int		main(int argc, char **argv)
{
	t_op_list	*oplist;
	int			fd;
	t_header	*header;
	char		*filename;

	filename = ft_getfilename(argc, argv);
	oplist = get_op_list(filename);
	header = ft_validation(oplist);
	filename = ft_getoutputfilename(filename);
	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_exit(strerror(errno), errno);
	ft_writehead(fd, header);
	ft_asmtobcode(fd, oplist);
	close(fd);
	ft_free(oplist, filename);
	system("leaks -q asm");
	return (0);
}
