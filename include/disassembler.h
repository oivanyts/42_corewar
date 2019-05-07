#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "op.h"

typedef unsigned char t_byte;

typedef struct	s_dasm
{
	t_header	header;
	int			len;
	t_byte		*bin;
	t_byte		*curr;

}				t_dasm;

void	disassembler(char *name);
void	read_binary(char *name, t_dasm *dasm);

#endif
