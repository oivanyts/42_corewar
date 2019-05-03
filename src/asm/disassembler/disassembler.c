#include "lexer.h"
#include "asm.h"
#include "disassembler.h"

void	print_header(t_dasm *dasm)
{
	ft_fprintf(dasm->fd, "%s \"%s\"\n", NAME_CMD_STRING, dasm->header.prog_name);
	ft_fprintf(dasm->fd, "%s \"%s\"\n\n", COMMENT_CMD_STRING, dasm->header.comment);
}

void	disassembler(char *name)
{
	t_dasm	dasm;
	char	*tmp;

	read_binaryy(name, &dasm);

	tmp = dasm.file_name;
	dasm.file_name = ft_strjoin(dasm.file_name, ".ds");
	free(tmp);
//
//	dasm.fd = open(dasm.file_name, O_RDWR);
//
	get_header(&dasm);
	print_header(&dasm);
	while (dasm.curr < dasm.len)
		do_operation(&dasm, &dasm.bin[dasm.curr]);
}