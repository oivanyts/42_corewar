#include "disassembler.h"
#include "asm.h"

void	set_type_arg(t_arg_type *targs, t_byte *bin)
{
	targs[0] = *bin >> 6;
	targs[1] = (*bin >> 4) & 0x03;
	targs[2] = (*bin >> 2) & 0x03;
}