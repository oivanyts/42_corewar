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

void load_dir_param(t_thread *sp, t_memory *mem)
{
	memory_init(mem, &sp->vm_memory[memory_tou32(mem) % MEM_SIZE], DIR_SIZE);
}

void load_dir_idx_param(t_thread *sp, t_memory *mem)
{
	memory_init(mem, &sp->vm_memory[(memory_tou32(mem) % IDX_MOD) % MEM_SIZE], DIR_SIZE);
}

void load_ind_param(t_thread *sp, t_memory *mem)
{
	memory_init(mem, &sp->vm_memory[(sp->op.ip + memory_tou16(mem)) % MEM_SIZE], DIR_SIZE);
}

void load_ind_idx_param(t_thread *sp, t_memory *mem)
{
	memory_init(mem, &sp->vm_memory[(sp->op.ip + (memory_tou16(mem) % IDX_MOD)) % MEM_SIZE], DIR_SIZE);
}

void load_reg_param(t_thread *sp, t_memory *mem)
{
	memory_init(mem, &sp->reg[memory_tou8(mem) - 1], REG_SIZE);
}

void load_param(t_thread *sp, t_memory *mem, uint8_t param_number)
{
	if (get_param_type(sp->op.tparams, param_number) == REG_CODE)
	{
		load_reg_param(sp, mem);
	}
	else if (get_param_type(sp->op.tparams, param_number) == DIR_CODE)
	{
		load_dir_param(sp, mem);
	}
	else if (get_param_type(sp->op.tparams, param_number) == IND_CODE)
	{
		load_ind_param(sp, mem);
	}
	else
	{
		handle_error(error_wrong_tparam);
	}
}

void load_idx_param(t_thread *sp, t_memory *mem, uint8_t param_number)
{
	if (get_param_type(sp->op.tparams, param_number) == DIR_CODE)
	{
		load_dir_idx_param(sp, mem);
	}
	else if (get_param_type(sp->op.tparams, param_number) == IND_CODE)
	{
		load_ind_idx_param(sp, mem);
	}
	else
	{
		handle_error(error_wrong_tparam);
	}
}

void f_live(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	int32_t p32;

	(void)p2;
	(void)p3;
	sp->lives += 1;
	load_param(sp, p1, 1);
	p32 = memory_tou32(p1);
	p32 = swap32((uint32_t*)&p32);
	if (((t_player*)sp->player)->number == -p32)
	{
		get_vm(0)->last_alive = ((t_player*)sp->player)->number;
	}
}

void f_ld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    (void)p3;
    if (get_param_type(sp->op.tparams, 1) == IND_CODE)
	{
		load_idx_param(sp, p1, 1);
	}
    else
	{
		load_param(sp, p1, 1);
	}
	memory_memmove(p2, p1);
    sp->cf = memory_iszero(p2);
}

void f_st(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    (void)sp;
    (void)p3;
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	memory_memmove(p2, p1);
}

void f_add(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
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
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_and(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void f_or(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_or(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void f_xor(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_xor(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void f_zjmp(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)p2;
	(void)p3;
	if (sp->cf)
		sp->ip = memory_tou32(p1) % IDX_MOD;
}

void f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_memory mem;

    memory_init(&mem, &sp->vm_memory[(sp->op.ip + memory_tou32(p1) + memory_tou32(p2)) % IDX_MOD], 4); //not exactly 4
	memory_memmove(p3, &mem);
}

void f_sti(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_memory mem;

	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	memory_init(&mem, &sp->vm_memory[(sp->op.ip + memory_tou32(p2) + memory_tou32(p3)) % IDX_MOD], 4); //not exactly 4
	memory_memmove(&mem, p1);

}

void f_fork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_player	*player;
    t_thread	tmp;
    uint16_t 	num;

    (void)p1;
	(void)p2;
    (void)p3;
    player = sp->player;
	ft_bzero(&tmp, sizeof(t_thread));
    ft_memcpy(&tmp.reg, &sp->reg, REG_SIZE * REG_NUMBER);
    tmp.player = sp->player;
	tmp.lives = 0;
    tmp.alive = 1;
    tmp.op.opcode = -1;
    tmp.vm_memory = sp->vm_memory;
    num = memory_tou16(p1);
    tmp.ip = (swap16(&num) % IDX_MOD) % MEM_SIZE;
    if (!threads_push_back(&player->threads, &tmp))
        handle_error(error_array_add);
}

void f_lld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3) //not sure if working
{
    (void)p3;
    memory_memmove(p2, p1);
    sp->cf = memory_iszero(p2);
}

void f_lldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_memory mem;
    uint32_t up1;
    uint32_t up2;

	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	up1 = swap32(p1->memory);
	up2 = swap32(p2->memory);
    memory_init(&mem, &sp->vm_memory[(sp->op.ip + up1 + up2)], REG_SIZE);
    memory_memmove(p3, &mem);
}

void f_lfork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_player *player;
    t_thread	tmp;
	uint16_t 	num;

    (void)p1;
    (void)p2;
    (void)p3;
    player = sp->player;
	ft_bzero(&tmp, sizeof(t_thread));
	ft_memcpy(&tmp.reg, &sp->reg, REG_SIZE * REG_NUMBER);
    tmp.player = sp->player;
	tmp.lives = 0;
    tmp.alive = 1;
    tmp.op.opcode = -1;
    tmp.vm_memory = sp->vm_memory;
	num = memory_tou16(p1);
	tmp.ip = swap16(&num) % MEM_SIZE;
    if (!threads_push_back(&player->threads, &tmp))
        handle_error(error_array_add);
}

void f_aff(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    (void)sp;
    (void)p2;
    (void)p3;
    ft_printf("%c", p1->memory);
}
