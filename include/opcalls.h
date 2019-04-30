/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcalls.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:14:27 by myaremen          #+#    #+#             */
/*   Updated: 2019/04/26 17:14:28 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPCALLS_H
# define OPCALLS_H

# include <stdint.h>
# include <stdbool.h>

typedef enum e_opcode
{
	oplowborder = 0,
	oplive = 1,
	opld,
	opst,
	opadd,
	opsub,
	opand,
	opor,
	opxor,
	opzjmp,
	opldi,
	opsti,
	opfork,
	oplld,
	oplldi,
	oplfork,
	opaff,
	ophighborder
} t_opcode;

typedef struct	s_op
{
	char	*name;
	uint32_t		args;
	uint8_t		targs[3];
	uint8_t		opcode;
	uint32_t		cycle;
	char	*descr;
	bool	codoctal;
	bool		tdir_size;
}				t_op;

typedef struct s_thread
{
	uint32_t ip;
	bool cf;
	uint32_t id;
	uint32_t reg[16];
	uint8_t  *vm_memory;
	uint32_t lives;
	bool alive;
	uint16_t wait;
} t_thread;

typedef struct s_opcall
{
	uint8_t opcode;
	void (*opfunc)(t_thread*, void*, void*, void*);
} t_opcall;

t_opcall opcalls[ophighborder - 1];

void f_live(t_thread *sp, void *p1, void *p2, void *p3);

void f_ld(t_thread *sp, void *p1, void *p2, void *p3);

void f_st(t_thread *sp, void *p1, void *p2, void *p3);

void f_add(t_thread *sp, void *p1, void *p2, void *p3);

void f_sub(t_thread *sp, void *p1, void *p2, void *p3);

void f_and(t_thread *sp, void *p1, void *p2, void *p3);

void f_or(t_thread *sp, void *p1, void *p2, void *p3);

void f_xor(t_thread *sp, void *p1, void *p2, void *p3);

void f_zjmp(t_thread *sp, void *p1, void *p2, void *p3);

void f_ldi(t_thread *sp, void *p1, void *p2, void *p3);

void f_sti(t_thread *sp, void *p1, void *p2, void *p3);

void f_fork(t_thread *sp, void *p1, void *p2, void *p3);

void f_lld(t_thread *sp, void *p1, void *p2, void *p3);

void f_lldi(t_thread *sp, void *p1, void *p2, void *p3);

void f_lfork(t_thread *sp, void *p1, void *p2, void *p3);

void f_aff(t_thread *sp, void *p1, void *p2, void *p3);

#endif
