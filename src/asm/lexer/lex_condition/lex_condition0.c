#include "asm.h"

int		lex_num(char *c)
{
	return (ft_isdigit(*c));
}

int		lex_r(char *c)
{
	return (*c == 'r');
}

int		lex_label_chars(char *c)
{
	char	*i;

	i = LABEL_CHARS;
	while (*i != '\0')
	{
		if (*i == *c)
			return (1);
		i++;
	}
	return (0);
}

int		lex_minus(char *c)
{
	return (*c == '-');
}

int		lex_direct_char(char *c)
{
	return (*c == DIRECT_CHAR);
}