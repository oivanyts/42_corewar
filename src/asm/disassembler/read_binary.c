#include "asm.h"
#include "disassembler.h"
#include "lexer.h"

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

static char	*reverse_string(char *name)
{
	char	*str;
	int		i;
	int 	len;

	i = 0;
	len = ft_strlen(name);
	str = (char*)ft_memalloc(len + 1);
	while (len--)
		str[i++] = name[len];
	return (str);
}

static void	validation(char *name, t_dasm *dasm)
{
	char	*rev_name;
	char	*tmp;

	rev_name = reverse_string(name);
	if (!str_cmp(rev_name, "roc."))
	{
		ft_printf("The file must be .cor extension!\n");
		exit(0);
	}
	tmp = ft_strdup(rev_name + 4);
	dasm->file_name = reverse_string(tmp);
	free(tmp);
	free(rev_name);
}

void		read_binaryy(char *name, t_dasm *dasm)
{
	int 	fd;
	t_byte	*p_bin;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("File \"%s\" does not exist!\n", name);
		exit(1);
	}
	validation(name, dasm);
	dasm->len = get_file_len(fd);
	dasm->bin = (t_byte*)ft_memalloc(dasm->len);
	p_bin = dasm->bin;
	while (read(fd, p_bin, 1) == 1)
		p_bin++;
	close(fd);
}