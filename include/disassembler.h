#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "op.h"
#include "libft.h"

typedef unsigned char t_byte;

typedef struct	s_dasm
{
	int 		fd;
	char		*file_name;
	t_header	header;
	int			len;
	t_byte		*bin;
	int			curr;
}				t_dasm;

typedef struct	s_oper
{
	t_arg_type	targs[3];
	struct s_op	*op;
	t_byte		*start;
	int			separators;
}				t_oper;

void	disassembler(char *name);
void	read_binaryy(char *name, t_dasm *dasm);
void	set_header(t_dasm *dasm);

int		get_int_from_pointer(void *p);
int		get_short_from_pointer(void *p);
int		get_char_from_pointer(void *p);

void	set_type_arg(t_arg_type *targs, t_byte *bin);
void	do_operation(t_dasm *dasm, t_byte *bin);

#endif
