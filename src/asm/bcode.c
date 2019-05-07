/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bcode.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:04:07 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/07 13:26:45 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_writenum(int fd, void *data, size_t size)
{
	while (size--)
	{
		write(fd, &data[size], 1);
	}
}

void	ft_writehead(int fd, t_header *header)
{
	ft_writenum(fd, &header->magic, 4);
	write(fd, header->prog_name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	ft_writenum(fd, &header->prog_size, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
}

int		ft_getcodeargs(t_token_list *toklist)
{
	unsigned char	codeargs;
	unsigned char	argnum;
	int				argtype;

	argnum = 6;
	codeargs = 0;
	while (toklist)
	{
		if ((argtype = ft_gettypearg(toklist->ident)))
		{
			if (argtype == T_REG)
				codeargs = codeargs | ((unsigned)REG_CODE << argnum);
			else if (argtype == T_DIR)
				codeargs = codeargs | ((unsigned)DIR_CODE << argnum);
			else if (argtype == T_IND)
				codeargs = codeargs | ((unsigned)IND_CODE << argnum);
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
		op = ft_getfuncname(toklst);
		write(fd, &op->opcode, 1);
		if (op->codoctal)
		{
			codearg = ft_getcodeargs(toklst);
			write(fd, &codearg, 1);
		}
	}
	else if (toklst->ident == DIRECT)
		ft_writenum(fd, toklst->data, op->dirsize);
	else if (toklst->ident == INDIRECT)
		ft_writenum(fd, toklst->data, IND_SIZE);
	else if (toklst->ident == REGISTER)
		ft_writenum(fd, toklst->data, 1);
}

void	ft_asmtobcode(int fd, t_op_list *oplist)
{
	t_token_list	*toklst;

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
