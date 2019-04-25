/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:55:42 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 04:36:25 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

#define TESTTESTTEST
bool	load_from_file(char	*filename)
{
	int	fd, rd, i = 0;
	unsigned char bitecode[MEM_SIZE];

	if (!(fd = open(filename, O_RDONLY)))
		return (false);
	rd = read(fd, bitecode, MEM_SIZE);
	while (i < rd)
	{
		ft_printf("%.2x%.2x ", bitecode[i], bitecode[i + 1]);
		i += 2;
		if (!(i % 16))
			ft_printf("\n");
	}
	return (true);
}