/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:47:27 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/27 13:30:44 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lexer.h"
#include "disassembler.h"

int		main(int argc, char **argv)
{
	t_op_list	*oplist;
	int			fd;
	t_header	*header;
	char		*filename;

	if (argc == 3 && ft_strequ("-d", argv[1]))
		disassembler(argv[2]);
	filename = ft_getfilename(argc, argv);
	oplist = get_op_list(filename);
	header = ft_validation(oplist);
	filename = ft_getoutputfilename(filename);
	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_exit(strerror(errno), errno);
	ft_writehead(fd, header);
	ft_asmtobcode(fd, oplist);
	close(fd);
	ft_printf("Writing output program to %s\n", filename);
	ft_free(oplist, filename);
	system("leaks -q asm");
	return (0);
}
