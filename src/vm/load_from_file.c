/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:55:42 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 05:13:31 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

void	output_binary(unsigned char *bitecode, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		ft_printf("%.2x%.2x ", bitecode[i], bitecode[i + 1]);
		i += 2;
		if (!(i % 16))
			ft_printf("\n");
	}
}

bool	load_from_file(char	*filename)
{
	int				fd;
	unsigned char	bitecode[MEM_SIZE];

	if (!(fd = open(filename, O_RDONLY)))
		return (false);
	output_binary(bitecode, (size_t)read(fd, bitecode, MEM_SIZE));

	return (true);
}