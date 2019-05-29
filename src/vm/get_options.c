#include "libft.h"
#include "vm.h"
char	*is_param(char *string, const char *options)
{
	char	*ret;
	if (*string++ != '-' || !*string)
		return (NULL);
	if ((ret = ft_strchr(options, *string)))
		return (ret);
	return (NULL);
}

int get_options(int	argc, char *argv[], const char *options)
{
	uint8_t n_op;
	uint8_t i = 1;
	char	*opt;
	t_vm	*vm;

	n_op = 0;
	vm = get_vm(0);
	while (i < argc)
	{
		if ((opt = is_param(argv[i], options)))
		{
			if (*opt == 'd' && *(opt + 1) == ':')
				vm->options.o_dump = ft_atoi((opt + 1));
			if (*opt == 's' && *(opt + 1) == ':')
				vm->options.o_stop = ft_atoi((opt + 1));
		}
		else
		{

		}
		i++;
	}
	return (2);
}