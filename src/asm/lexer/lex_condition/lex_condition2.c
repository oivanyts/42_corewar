#include "asm.h"

int		lex_comment(char *c)
{
	return (ft_strcmp(COMMENT_CMD_STRING, c) == 0);
}

int		lex_whitespace(char *c)
{
	return (*c == ' ' || *c == '\t');
}

int		lex_other(char *c)
{
	return (1);
}