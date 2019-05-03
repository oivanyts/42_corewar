/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:47:27 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/03 12:28:24 by npiatiko         ###   ########.fr       */
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

int 	ft_getcodeargs(t_token_list *toklist)
{
	int			codeargs;
	char		argnum;
	char 		argtype;

	argnum = 6;
	codeargs = 0;
	while (toklist)
	{
		if ((argtype = ft_typearg(toklist->ident)))
		{
			if (argtype == T_REG)
				codeargs = (codeargs) | (REG_CODE << argnum);
			else if (argtype == T_DIR)
				codeargs = (codeargs) | (DIR_CODE << argnum);
			else if (argtype == T_IND)
				codeargs = (codeargs) | (IND_CODE << argnum);
			argnum -= 2;
		}
		toklist = toklist->next;
	}
	return (codeargs);
}

void	ft_writebcode(int fd, t_token_list *toklst)
{
	int				codearg;
	static t_op		*op;

	if (toklst->ident == INSTRUCTION)
	{
		op = ft_checkname(toklst);
		write(fd, &op->opcode, 1);
		if (op->codoctal)
		{
			codearg = ft_getcodeargs(toklst);
			write(fd, &codearg, 1);
		}
	}
	else if (toklst->ident == DIRECT)
		ft_write(fd, toklst->data, op->dirsize);
	else if (toklst->ident == INDIRECT)
		ft_write(fd, toklst->data, IND_SIZE);
	else if (toklst->ident == REGISTER)
		ft_write(fd, toklst->data, 1);
}

void	ft_asmtobcode(int fd, t_op_list *oplist)
{
	t_token_list	*toklst;
	int				codearg;
	static t_op		*op;

	while (oplist)
	{
		toklst = oplist->token_list;
		while (toklst)
		{
			ft_writebcode(fd, toklst);
			toklst = toklst->next;
		}
		oplist = oplist->next;
	}
}

int		main(int argc, char **argv)
{
	t_op_list *oplist;
	int fd;
	t_header *header;

	header = ft_memalloc(sizeof(t_header));
	oplist = get_op_list("vm_champs/champs/ex.s");
//	system("leaks -q asm");
//	print_identifiers(oplist);
//	ft_printf("===============================\n");
	ft_validation(oplist, header);
	header->prog_size = ft_calcprogsize(oplist);
	ft_replacelable(oplist);
	if ((fd = open("test", O_RDWR | O_CREAT | O_TRUNC, 0755)) < 0)
		ft_exit(strerror(errno), errno);
	ft_writehead(fd, header);
	ft_asmtobcode(fd, oplist);
//	ft_printf("\n%hhb\n", (3 << 2) | 1);
	close(fd);
	return (0);
}



