/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:12:13 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/07 13:24:09 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_getfilename(int ac, char **av)
{
	char	*filename;
	int		fd;

	ac > 3 ? ft_exit("To much args.", 23) : 0;
	ac < 2 ? ft_exit("To few args.", 23) : 0;
	ac == 3 && !ft_strequ("-d", av[1]) ? ft_exit("Unknown param.", 23) : 0;
	filename = av[ac == 2 ? 1 : 2];
	if ((fd = open(filename, O_DIRECTORY)) > 0)
	{
		close(fd);
		ft_exit("File is DIR.", 24);
	}
	else if ((fd = open(filename, O_RDONLY)) > 0)
	{
		close(fd);
		if (!ft_strequ(&filename[ft_strlen(filename) - 2], ".s"))
			ft_exit("File must be *.s", 24);
	}
	else
		ft_exit(strerror(errno), errno);
	return (filename);
}

char	*ft_getoutputfilename(char *filename)
{
	char *name;

	name = ft_strnew(ft_strlen(filename) + 2);
	ft_memcpy(name, filename, ft_strlen(filename) - 1);
	ft_memcpy(&name[ft_strlen(filename) - 1], "MYY", 3);
	return (name);
}

void	ft_freetok(t_token_list *toklist)
{
	t_token_list	*toktmp;

	while (toklist)
	{
		toktmp = toklist;
		toklist = toklist->next;
		free(toktmp->data);
		free(toktmp);
	}
}

void	ft_free(t_op_list *oplist, char *filename)
{
	t_op_list		*optmp;

	optmp = oplist;
	free(filename);
	while (oplist)
	{
		optmp = oplist;
		oplist = oplist->next;
		ft_freetok(optmp->token_list);
		free(optmp);
	}
}
