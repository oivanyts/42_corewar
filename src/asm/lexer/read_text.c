#include "asm.h"

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

char		*read_text_from(char *name) //Don't check '\n' at EOF
{
	int 	fd;
	char	*text;
	char	*p_text;

	fd = open(name, O_RDONLY);
	text = (char*)ft_memalloc(get_file_len(fd) + 1);
	p_text = text;
	while (read(fd, p_text, 1) == 1)
	{
		p_text++;
	}
	return (text);
}