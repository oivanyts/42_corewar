#include "asm.h"
#include "disassembler.h"

static int	get_file_len(fd)
{
	char	buf[1];
	int		len;

	len = 0;
	while (read(fd, buf, 1) == 1)
		len++;
	lseek(fd, 0, SEEK_SET);
	return (len);
}

void		read_binary(char *name, t_dasm *dasm)
{
	int 	fd;
	t_byte	*p_bin;

	fd = open(name, O_RDONLY);
	dasm->len = get_file_len(fd);
	dasm->bin = (t_byte*)ft_memalloc(dasm->len);
	p_bin = dasm->bin;
	while (read(fd, p_bin, 1) == 1)
		p_bin++;
	close(fd);
}