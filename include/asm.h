/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:19:23 by npiatiko          #+#    #+#             */
/*   Updated: 2019/05/22 13:25:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"
# include <errno.h>

typedef enum	e_identifier
{
	COMMENT,
	NAME,
	LABEL,
	INSTRUCTION,
	REGISTER,
	INDIRECT,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT_LABEL,
	SEPARATOR,
	STRING,
	ENDLINE,
	END
}				t_identifier;

typedef struct	s_asm
{
	int					row;
	int					col;
	struct s_fsm		*fsm;
	struct s_op_list	*op_list;
	struct s_token_list	*token_list;
	int					(*lex_condition[15])(char *c);
	int					(*id_state[15])(struct s_asm *a);
	void				(*errors[3])(struct s_asm *a);
}				t_asm;

typedef struct	s_fsm
{
	int					st_col;
	int					st_row;
	char				*start;
	char				*curr;
	int					state;
	char				*code;
}				t_fsm;

typedef struct	s_op_list
{
	struct s_token_list	*token_list;
	int					instrsize;
	int					instrstart;
	struct s_op_list	*next;
}				t_op_list;

typedef struct	s_token_list
{
	enum e_identifier	ident;
	void				*data;
	int					col;
	int					row;
	struct s_token_list	*next;
}				t_token_list;

typedef struct	s_op
{
	char	*name;
	int		args;
	int		targs[3];
	int		opcode;
	int		cycle;
	char	*descr;
	int		codoctal;
	int		dirsize;
}				t_op;

static char		*g_ident_str[] =
{
	"COMMENT", "NAME", "LABEL", "INSTRUCTION",
	"REGISTER", "INDIRECT", "DIRECT", "DIRECT_LABEL",
	"INDIRECT_LABEL", "SEPARATOR", "STRING", "ENDLINE", "END"
};
static t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, DIR_SIZE},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, DIR_SIZE},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, DIR_SIZE},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, DIR_SIZE},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, DIR_SIZE},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, DIR_SIZE},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, DIR_SIZE},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, DIR_SIZE},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, IND_SIZE},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		10, 25, "load index", 1, IND_SIZE},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		11, 25, "store index", 1, IND_SIZE},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, IND_SIZE},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, DIR_SIZE},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, "long load index", 1, IND_SIZE},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, IND_SIZE},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, DIR_SIZE},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

t_header		*ft_validation(t_op_list *oplist);
void			ft_exit(char *stre, int e);
int				ft_getprogsize(t_op_list *oplist);
t_op			*ft_getfuncname(t_token_list *toklst);
void			ft_replacelable(t_op_list *oplist);
int				ft_searchlable(t_op_list *oplist, t_token_list *toklst);
int				ft_gettypearg(t_identifier ident);
void			ft_errhandler(t_token_list *toklst);
int				ft_toklistlen(t_token_list *toklst);
int				ft_oplistlen(t_op_list *oplist);
char			*ft_getfilename(int ac, char **av);
char			*ft_getoutputfilename(char *filename);
void			ft_asmtobcode(int fd, t_op_list *oplist);
void			ft_writehead(int fd, t_header *header);
void			ft_free(t_op_list *oplist, char *filename);
#endif
