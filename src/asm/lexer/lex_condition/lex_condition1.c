#include "asm.h"
#include "lexer.h"

int		lex_separator_char(char *c)
{
	return (*c == SEPARATOR_CHAR);
}

int		lex_label_char(char *c)
{
	return (*c == LABEL_CHAR);
}

int		lex_commentary(char *c)
{
	return (*c == COMMENT_CHAR || *c == ALT_COMMENT_CHAR);
}

int		lex_quote(char *c)
{
	return (*c == '"');
}

int 	lex_name(char *c)
{
	return (str_cmp(c, NAME_CMD_STRING));
}