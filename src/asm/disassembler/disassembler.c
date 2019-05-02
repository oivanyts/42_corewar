#include "lexer.h"
#include "asm.h"
#include "disassembler.h"

void	disassembler(char *name)
{
	t_dasm	dasm;

	read_binary(name, &dasm);

}