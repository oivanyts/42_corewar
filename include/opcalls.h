/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcalls.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:14:27 by myaremen          #+#    #+#             */
/*   Updated: 2019/05/02 01:46:40 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPCALLS_H
# define OPCALLS_H

# include <stdint.h>
# include <stdbool.h>
# include "abstract_cpu.h"

typedef struct	s_op
{
	char		*name;
	uint32_t	args;
	uint8_t		targs[3];
	uint8_t		opcode;
	uint32_t	cycle;
	char		*descr;
	bool		codoctal;
	bool		tdir_size;
}				t_op;

typedef struct	s_decoded_op
{
	uint32_t	ip;
	uint8_t		tparams;
	uint8_t		opcode;
	t_memory	args[3];
	bool		valid;
}				t_decoded_op;

/*
**	*player;	указатель на игрока, который породил каретку
**	ip;			код операции, на которой стоит каретка
**	cf;			Флаг, который могут изменять некоторые операции
**	reg[16];	регистры, количество которых задано в константе
**	*vm_memory	указатель на оперативную память
**	lives;		сколько раз поток сообщил о том, что жив
**	alive;		определяет, жив ли поток
**	last_live;
**	wait;		сколько еще ждать до выполнения операции
**	op;			содержит информацию об операции, которая ожидает выполнения
**	processing;
*/
typedef struct	s_thread
{
	void			*player;
	uint32_t		ip;
	bool			cf;
	uint32_t		reg[16];
	uint8_t			*vm_memory;
	uint32_t		lives;
	bool			alive;
	uint32_t		last_live;
	uint16_t		wait;
	t_decoded_op	op;
	bool			processing;
}				t_thread;

typedef struct	s_opcall
{
	uint8_t	opcode;
	void	(*opfunc)(t_thread*, t_memory*, t_memory*, t_memory*);
}				t_opcall;

t_opcall		g_opcalls[16];
t_op			g_op_tab[17];
uint32_t		swap32(uint32_t toswap);
uint16_t		swap16(uint16_t toswap);
void			f_live(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_ld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_st(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_add(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_sub(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_and(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_or(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_xor(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_zjmp(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_sti(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_fork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_lld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_lldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_lfork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			f_aff(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);
void			load_dir_param(t_thread *sp, t_memory *mem);
void			load_dir_idx_param(t_thread *sp, t_memory *mem);
void			load_ind_param(t_thread *sp, t_memory *mem);
void			load_reg_param(t_thread *sp, t_memory *mem);
void			load_param(t_thread *sp, t_memory *mem, uint8_t param_number);
void			load_idx_param
							(t_thread *sp, t_memory *mem, uint8_t param_number);
void output_operation(t_thread *sp);

#endif
