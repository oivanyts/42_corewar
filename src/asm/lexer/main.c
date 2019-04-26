//
// Created by Vladyslav USLYSTYI on 2019-04-25.
//

#include "asm.h"
#include "lexer.h"

int main()
{
//	char	*text;
//	t_fsm	fsm;
//
//	read_table("machine", &fsm);
//	int col = 0;
//	int row = 0;
//	while (row < fsm.tab_row)
//	{
//		col = 0;
//		while (col < fsm.tab_col)
//			ft_printf("%3i ", fsm.table[row][col++]);
//		ft_printf("\n");
//		row++;
//	}
//	text = read_text_from("new.s");
//	ft_printf("%s", text);
	char	*text = "Hello world";
	char	*p = text + 6;

	printf("%s\n%s\n%lu", text, p, p - text);
}