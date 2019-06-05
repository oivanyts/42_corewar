//
// Created by Nickolay PIATIKOP on 2019-06-05.
//
#include "opcalls.h"
#include "vm.h"

t_opcall	g_opcalls[16] =
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

void	load_dir_param(t_thread *sp, t_memory *mem)
{
	(void)sp;
	(void)mem;
}

void	load_dir_idx_param(t_thread *sp, t_memory *mem)
{
	int16_t addr;

	addr = memory_tou16(mem);
	addr = swap16(addr);
	memory_init(mem, &sp->vm_memory[(sp->op.ip + (addr % IDX_MOD)) % MEM_SIZE],
				mem->memory_size);
}

void	load_ind_param(t_thread *sp, t_memory *mem)
{
	int16_t addr;

	addr = memory_tou16(mem);
	addr = swap16(addr);
	memory_init(mem, &sp->vm_memory[(sp->op.ip
		+ (addr % IDX_MOD)) % MEM_SIZE], DIR_SIZE);
}

void	load_reg_param(t_thread *sp, t_memory *mem)
{
	memory_init(mem, &sp->reg[memory_tou8(mem) - 1], REG_SIZE);
}

void	load_param(t_thread *sp, t_memory *mem, uint8_t param_number)
{
	if (get_param_type(sp->op.opcode, sp->op.tparams, param_number)
		== T_REG)
	{
		load_reg_param(sp, mem);
	}
	else if (get_param_type(sp->op.opcode, sp->op.tparams, param_number)
		== T_DIR)
	{
		load_dir_param(sp, mem);
	}
	else if (get_param_type(sp->op.opcode, sp->op.tparams, param_number)
		== T_IND)
	{
		load_ind_param(sp, mem);
	}
	else
	{
		handle_error(error_wrong_tparam);
	}
}
