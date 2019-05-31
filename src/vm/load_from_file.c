/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:55:42 by oivanyts          #+#    #+#             */
/*   Updated: 2019/05/27 13:30:44 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

void	output_binary(uint8_t *bytecode, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		ft_printf("%.2x%.2x ", bytecode[i], bytecode[i + 1]);
		i += 2;
		if (!(i % 16))
			ft_printf("\n");
	}
	ft_printf("\n");
}

unsigned int reverse_byte(unsigned int old)
{
	return ((old >> 24) | ((old >> 8) & 0xff00) | ((old << 8) & 0xff0000) |
	old << 24);
}

void load_from_file(char *filename, t_player *player, uint8_t memory[])
{
	int		fd;
	size_t	ret;
	uint8_t	bytes[MEM_SIZE];

	(fd = open(filename, O_RDONLY)) > 0 ? 0 : handle_error(error_opening_file);
	(ret = (size_t)read(fd, bytes, MEM_SIZE)) > 0 ? 0 : handle_error(4);
	player->header.magic = *(uint32_t *)&bytes;
	if ((IS_BIG_ENDIAN && COREWAR_EXEC_MAGIC != player->header.magic)
		|| (!IS_BIG_ENDIAN &&
			reverse_byte(COREWAR_EXEC_MAGIC) != player->header.magic))
		handle_error(error_wrong_magic);
	if (ret - (12 + PROG_NAME_LENGTH + COMMENT_LENGTH + 4) > CHAMP_MAX_SIZE)
	{
		handle_error(error_champ_size);
	}
	ft_memcpy(player->header.prog_name, &bytes[4], PROG_NAME_LENGTH);
	player->header.prog_size = *(uint32_t *)&bytes[8 + PROG_NAME_LENGTH];
	if (!IS_BIG_ENDIAN)
		player->header.prog_size = reverse_byte(player->header.prog_size);
	ft_memcpy(player->header.comment, &bytes[12 + PROG_NAME_LENGTH], COMMENT_LENGTH);
	ft_memcpy(memory, &bytes[12 + PROG_NAME_LENGTH + COMMENT_LENGTH + 4],
			  (size_t)player->header.prog_size);
	close(fd);
}

void init_carridge(t_player *player, uint8_t i, uint8_t *memory, int gap)
{
    t_thread	tmp;

    ft_bzero(&tmp, sizeof(t_thread));
    tmp.player = player;
    tmp.lives = 0;
    tmp.alive = 1;
    tmp.processing = 0;
    tmp.vm_memory = memory;
    tmp.ip = (uint32_t)(gap * i);
    tmp.reg[0] = swap32(-player->number);
    if (!threads_push_back(player->threads, &tmp))
        handle_error(error_array_add);
}
