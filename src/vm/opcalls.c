#include "opcalls.h"
#include "vm.h"
#include "vs.h"

t_opcall opcalls[16] =
{
	{1, f_live},
	{2, f_ld},
	{3, f_st},
	{4, f_add},
	{5, f_sub},
	{6, f_and},
	{7, f_or},
	{8, f_xor},
	{9, f_zjmp},
	{10, f_ldi},
	{11, f_sti},
	{12, f_fork},
	{13, f_lld},
	{14, f_lldi},
	{15, f_lfork},
	{16, f_aff},
};

void load_dir_param(t_thread *sp, t_memory *mem)
{
	(void)sp;
	(void)mem;
}

void load_dir_idx_param(t_thread *sp, t_memory *mem)
{
	int16_t addr;

	addr = memory_tou16(mem);
	addr = swap16(addr);
	memory_init(mem, &sp->vm_memory[(sp->op.ip + (addr % IDX_MOD)) % MEM_SIZE], mem->memory_size);
}

void load_ind_param(t_thread *sp, t_memory *mem)
{
	int16_t addr;

	addr = memory_tou16(mem);
	addr = swap16(addr);
	memory_init(mem, &sp->vm_memory[(sp->op.ip + (addr % IDX_MOD)) % MEM_SIZE], DIR_SIZE);
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
		load_ind_param(sp, mem);
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
	p32 = swap32(p32);
	if (((t_player*)sp->player)->number == -p32)
	{
		get_vm(0)->last_alive = ((t_player*)sp->player)->number;
		g_vsmap[sp->op.ip].live = 50;
		g_vsmap[sp->op.ip].liveplayer = ((t_player*)sp->player)->number;
	}
}

void f_ld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    (void)p3;
	if (memory_tou8(p2) == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
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
	if (get_param_type(sp->op.tparams, 2) == IND_CODE)
	{
//		mvwprintw(g_vs->info_win, 6, 3, "!!=%d", ((uint8_t *)p2->memory - &sp->vm_memory[0]));
		ft_changememvs(((uint8_t *)p2->memory - &sp->vm_memory[0]), ((t_player *)sp->player)->number);
//		wrefresh(g_vs->info_win);
	}
}

void f_add(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	*(uint32_t*)p3->memory = swap32(swap32(memory_tou32(p1)) + swap32(memory_tou32(p2)));
	//memory_add(p3, p1, p2);
	sp->cf = memory_iszero(p3);
}

void f_sub(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	*(uint32_t*)p3->memory = swap32(swap32(memory_tou32(p1)) - swap32(memory_tou32(p2)));
	//memory_subtract(p3, p1, p2);
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
	{
		load_dir_idx_param(sp, p1);
		sp->ip = (uint8_t*)p1->memory - sp->vm_memory;
	}
}

void f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory mem;
	int32_t up1;
	int32_t up2;

	if (memory_tou8(p3) == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	if (get_param_type(sp->op.tparams, 1) == REG_CODE)
	{
		up1 = swap32(memory_tou32(p1));
	}
	else
	{
		up1 = (int16_t)swap16(memory_tou16(p1));
	}
	//up1 = swap16(memory_tou16(p1));
	if (get_param_type(sp->op.tparams, 2) == REG_CODE)
	{
		up2 = swap32(memory_tou32(p2));
	}
	else
	{
		up2 = (int16_t)swap16(memory_tou16(p2));
	}
	//up2 = swap32(memory_tou32(p2));
	memory_init(&mem, &sp->vm_memory[(sp->op.ip + (up1 + up2) % IDX_MOD) % MEM_SIZE], REG_SIZE);
	memory_memmove(p3, &mem);
}

void f_sti(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory mem, mem2;
	int32_t up1;
	int32_t up2;
	int32_t up3;

	if (get_vm(0)->cycle >= 2290)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	up1 = (memory_tou32(p1));
	if (get_param_type(sp->op.tparams, 2) == REG_CODE)
	{
		up2 = swap32(memory_tou32(p2));
	}
	else
	{
		up2 = (int16_t)swap16(memory_tou16(p2));
	}
	//up2 = swap16(memory_tou16(p2));
	if (get_param_type(sp->op.tparams, 3) == REG_CODE)
	{
		up3 = swap32(memory_tou32(p3));
	}
	else
	{
		up3 = (int16_t)swap16(memory_tou16(p3));
	}
	//up3 = swap16(memory_tou16(p3));
	memory_init(&mem2, &up1, REG_SIZE);
	memory_init(&mem, &sp->vm_memory[(sp->op.ip + (up2 + up3) % IDX_MOD) % MEM_SIZE], DIR_SIZE);
	memory_memmove(&mem, p1);
	ft_changememvs((sp->op.ip + (up2 + up3) % IDX_MOD) % MEM_SIZE, ((t_player *)sp->player)->number);
//	mvwprintw(g_vs->info_win, 6, 3, "!!=%d", (sp->op.ip + (up2 + up3) % IDX_MOD) % MEM_SIZE);
//	wrefresh(g_vs->info_win);

}

void f_fork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_player	*player;
    t_thread	tmp;

	(void)p2;
    (void)p3;
    load_idx_param(sp, p1, 1);
	player = sp->player;
	ft_memcpy(&tmp, sp, sizeof(t_thread));
	tmp.ip = (uint8_t*)p1->memory - sp->vm_memory;
	tmp.processing = 0;
	if (!threads_push_back(player->threads, &tmp))
	{
		handle_error(error_array_add);
	}
}

void f_lld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	int16_t addr;

	(void)p3;
	if (get_param_type(sp->op.tparams, 1) == T_DIR)
	{
		load_param(sp, p1, 1);
	}
	else
	{
		addr = memory_tou16(p1);
		addr = swap16(addr);
		memory_init(p1, &sp->vm_memory[(sp->op.ip + addr) % MEM_SIZE], DIR_SIZE);
	}
	load_param(sp, p2, 2);
	memory_memmove(p2, p1);
	sp->cf = memory_iszero(p2);
}

void f_lldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory mem;
	int32_t up1;
	int32_t up2;

	if (memory_tou8(p3) == 1)
	{
		get_vm(0);
	}
	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	if (get_param_type(sp->op.tparams, 1) == REG_CODE)
	{
		up1 = swap32(memory_tou32(p1));
	}
	else
	{
		up1 = (int16_t)swap16(memory_tou16(p1));
	}
	//up1 = swap16(memory_tou16(p1));
	if (get_param_type(sp->op.tparams, 2) == REG_CODE)
	{
		up2 = swap32(memory_tou32(p2));
	}
	else
	{
		up2 = (int16_t)swap16(memory_tou16(p2));
	}
	//up2 = swap16(memory_tou16(p2));
	memory_init(&mem, &sp->vm_memory[(sp->op.ip + up1 + up2) % MEM_SIZE], REG_SIZE);
	memory_memmove(p3, &mem);
}

void f_lfork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    t_player *player;
    t_thread	tmp;
	int16_t addr;

    (void)p2;
    (void)p3;
    player = sp->player;
	ft_memcpy(&tmp, sp, sizeof(t_thread));
	tmp.processing = 0;
	addr = memory_tou16(p1);
	addr = swap16(addr);
	memory_init(p1, &sp->vm_memory[(sp->op.ip + addr) % MEM_SIZE], p1->memory_size);
	tmp.ip = (uint8_t*)p1->memory - sp->vm_memory;
    if (!threads_push_back(player->threads, &tmp))
        handle_error(error_array_add);
}

void f_aff(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
    (void)sp;
    (void)p2;
    (void)p3;
    load_param(sp, p1, 1);
    ft_printf("%c", swap32(memory_tou32(p1)));
}
