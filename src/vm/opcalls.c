#include "opcalls.h"
#include "vm.h"

t_opcall opcalls[ophighborder] =
{
	{oplive, f_live},
	{opld, f_ld},
	{opst, f_st},
	{opadd, f_add},
	{opsub, f_sub},
	{opand, f_and},
	{opor, f_or},
	{opxor, f_xor},
	{opzjmp, f_zjmp},
	{opldi, f_ldi},
	{opsti, f_sti},
	{opfork, f_fork},
	{oplld, f_lld},
	{oplldi, f_lldi},
	{oplfork, f_lfork},
	{opaff, f_aff},
};

void f_live(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)p2;
	(void)p3;
	sp->lives += 1;
	get_vm(0)->last_alive = memory_tou32(p1);
}

void f_ld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_st(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_add(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	memory_add(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void f_sub(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	memory_subtract(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void f_and(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_or(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_xor(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_zjmp(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_sti(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_fork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_lld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_lldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_lfork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}

void f_aff(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;(void)p1;(void)p2;(void)p3;
}
