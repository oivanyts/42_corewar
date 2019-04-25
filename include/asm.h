#ifndef ASM_H
#define ASM_H

#include "op.h"
#include "libft.h"
typedef enum e_identifier
{
	COMMENT, NAME, LABEL, INSTRUCTION,
	REGISTER, INDIRECT, DIRECT, DIRECT_LABEL,
	INDIRECT_LABEL, SEPARATOR, STRING
}			t_identifier;

typedef struct 	s_op_list					//Структура для зберігання списку операцій (одна строка - одна операція)
											//Операція буде розбита на токени.
{
	struct s_token_list	*token_list;		//Для зберігання списку з токенами
	struct s_op_list	*next;				//Перехід на наступний токен
}				t_op_list;

typedef struct 	s_token_list
{
	enum e_identifier		ident;			//ідентифікатор токену (один зі списку нижче)
	char				*data;				//Для зберігання самої строки, що відповідає даному токену
	int 				col;				//Номер колонки (де знаходиться перший символ токену)
	int 				row;				//Номер рядка
	struct s_token_list	*next;
}				t_token_list;

typedef struct s_op
{
	char	*instr;
	int 	args;
	int 	targs[3];
	int		opcode;
	int 	cycle;
	char 	*name;
	int		codoctal;
	int 	some;
}t_op;
char g_ident_str[11][20] =
		{
				"COMMENT", "NAME", "LABEL", "INSTRUCTION",
				"REGISTER", "INDIRECT", "DIRECT", "DIRECT_LABEL",
				"INDIRECT_LABEL", "SEPARATOR", "STRING"
		};

#endif //COREWAR_ASM_H
