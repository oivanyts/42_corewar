
#include "vm.h"

int main(int argc, char *argv[])
{

	ft_printf("test %s %d\n", argv[1], argc);
	load_from_file(argv[1]);
	return 0;
}