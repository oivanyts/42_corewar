#include "asm.h"
#include "disassembler.h"

static void		read_magic(t_dasm *dasm, t_header *header)
{

	header->magic = get_int_from_pointer(dasm->bin);
	if (header->magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("The file is not binary execute for Corewar!");
		exit(1);
	}
	dasm->curr += sizeof(header->magic);
}

static void		read_prog_name(t_dasm *dasm, t_header *header)
{
	ft_strncpy(header->prog_name,
			   (const char*)(dasm->bin + dasm->curr), PROG_NAME_LENGTH + 1);
	dasm->curr += PROG_NAME_LENGTH + 4;
}

static void		read_prog_size(t_dasm *dasm, t_header *header)
{

	header->prog_size = get_int_from_pointer(dasm->bin + dasm->curr);
	dasm->curr += sizeof(header->prog_size);
}

static void		read_comment(t_dasm *dasm, t_header *header)
{
	ft_strncpy(header->comment,
			(const char*)(dasm->bin + dasm->curr), COMMENT_LENGTH + 1);
	dasm->curr += COMMENT_LENGTH + 4;
}

void			set_header(t_dasm *dasm)
{
	dasm->curr = 0;
	read_magic(dasm, &dasm->header);
	read_prog_name(dasm, &dasm->header);
	read_prog_size(dasm, &dasm->header);
	read_comment(dasm, &dasm->header);
	if (dasm->len - dasm->curr != (int)dasm->header.prog_size)
	{
		ft_printf("Your binary file is broken.\n");
		exit(1);
	}
}