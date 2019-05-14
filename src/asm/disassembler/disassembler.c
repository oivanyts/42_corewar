#include "lexer.h"
#include "asm.h"
#include "disassembler.h"

static void	print_header(t_dasm *dasm)
{
	ft_printf_fd(dasm->fd, "%s \"%s\"\n", NAME_CMD_STRING, dasm->header.prog_name);
	ft_printf_fd(dasm->fd, "%s \"%s\"\n\n", COMMENT_CMD_STRING, dasm->header.comment);
}

void		disassembler(char *name)
{
	t_dasm	dasm;
	char	*tmp;

	read_binaryy(name, &dasm);
	tmp = dasm.file_name;
	dasm.file_name = ft_strjoin(dasm.file_name, ".ds");
	free(tmp);
	if ((dasm.fd = open(dasm.file_name, O_CREAT | O_RDWR | O_TRUNC,
			S_IWRITE | S_IREAD)) < 0)
	{
		ft_printf("File \"%s\" can't be created.", dasm.file_name);
		exit(1);
	}
	set_header(&dasm);
	print_header(&dasm);
	while (dasm.curr < dasm.len)
		do_operation(&dasm, &dasm.bin[dasm.curr]);
	free(dasm.file_name);
	free(dasm.bin);
	close(dasm.fd);
	exit(0);
}