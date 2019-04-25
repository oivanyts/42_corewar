/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:55:42 by oivanyts          #+#    #+#             */
/*   Updated: 2019/04/25 08:23:04 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

void	output_binary(uint8_t *bitecode, size_t size)
{
//	size_t i;
//
//	i = 0;
//	while (i < size)
//	{
//		ft_printf("%.2x%.2x ", bitecode[i], bitecode[i + 1]);
//		i += 2;
//		if (!(i % 16))
//			ft_printf("\n");
//	}
//	ft_printf("\n");
}

int	reverse_byte(int old)
{
	return ((old >> 24) | ((old >> 8) & 0xff00) | ((old << 8) & 0xff0000) | old << 24);
}

bool	load_from_file(char	*filename, int num, t_player *player)
{
	int		fd;
	uint8_t	bitecode[MEM_SIZE];

	if (!(fd = open(filename, O_RDONLY)))
		return (false);
	ft_printf("opened %s\n", filename);
	output_binary(bitecode, (size_t)read(fd, bitecode, MEM_SIZE));
	player->header.magic = *(uint32_t *)&bitecode;
	if ((IS_BIG_ENDIAN && COREWAR_EXEC_MAGIC != player->header.magic)
		|| (!IS_BIG_ENDIAN &&
			reverse_byte(COREWAR_EXEC_MAGIC) != player->header.magic))
		handle_error(3);
	ft_memcpy(player->header.prog_name, &bitecode[4], PROG_NAME_LENGTH);
	player->header.prog_size = *(uint32_t *)&bitecode[8 + PROG_NAME_LENGTH];
	ft_memcpy(player->header.comment, &bitecode[12 + PROG_NAME_LENGTH], COMMENT_LENGTH);
	ft_printf("NAME [%s]\nSIZE [%d]\nCOMMENT [%s]\n\n", player->header.prog_name, reverse_byte(player->header.prog_size), player->header.comment);
	return (true);
}