/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:27:30 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 12:45:51 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_file_len(int fd)
{
	char	buf[1];
	int		len;

	len = 0;
	while ((read(fd, buf, 1)) == 1)
		len++;
	lseek(fd, 0, SEEK_SET);
	return (len);
}

char		*read_text_from(char *name)
{
	int		fd;
	char	*text;
	char	*p_text;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("File does not exist!");
		exit(1);
	}
	text = (char*)ft_memalloc(get_file_len(fd) + 1);
	p_text = text;
	while ((read(fd, p_text, 1)) == 1)
		p_text++;
	close(fd);
	return (text);
}
