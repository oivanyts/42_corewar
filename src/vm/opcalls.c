#include "opcalls.h"
#include "vm.h"
#include "vs.h"

void	f_fork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
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

void	f_lld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	int16_t addr;

	(void)p3;
	if (((t_player*)(sp->player))->number == 1)
	{
		get_vm(0);
	}
	if (get_param_type(sp->op.opcode, sp->op.tparams, 1) == T_DIR)
	{
		load_param(sp, p1, 1);
	}
	else
	{
		addr = memory_tou16(p1);
		addr = swap16(addr);
		memory_init(p1,
			&sp->vm_memory[(sp->op.ip + addr) % MEM_SIZE], DIR_SIZE);
	}
	load_param(sp, p2, 2);
	memory_memmove(p2, p1);
	sp->cf = memory_iszero(p2);
}

void	f_lldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_memory	mem;
	int32_t		up1;
	int32_t		up2;

	load_param(sp, p1, 1);
	load_param(sp, p2, 2);
	load_param(sp, p3, 3);
	if (get_param_type(sp->op.opcode, sp->op.tparams, 1) == T_REG)
		up1 = swap32(memory_tou32(p1));
	else
		up1 = (int16_t)swap16(memory_tou16(p1));
	if (get_param_type(sp->op.opcode, sp->op.tparams, 2) == T_REG)
		up2 = swap32(memory_tou32(p2));
	else
		up2 = (int16_t)swap16(memory_tou16(p2));
	memory_init(&mem,
		&sp->vm_memory[(sp->op.ip + up1 + up2) % MEM_SIZE], REG_SIZE);
	memory_set_bounds(&mem, sp->vm_memory, sp->vm_memory + MEM_SIZE);
	memory_memmove(p3, &mem);
}

void	f_lfork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	t_player	*player;
	t_thread	tmp;
	int16_t		addr;

	(void)p2;
	(void)p3;
	player = sp->player;
	ft_memcpy(&tmp, sp, sizeof(t_thread));
	tmp.processing = 0;
	addr = memory_tou16(p1);
	addr = swap16(addr);
	memory_init(p1,
		&sp->vm_memory[(sp->op.ip + addr) % MEM_SIZE], p1->memory_size);
	tmp.ip = (uint8_t*)p1->memory - sp->vm_memory;
	if (!threads_push_back(player->threads, &tmp))
		handle_error(error_array_add);
}

void	f_aff(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3)
{
	(void)sp;
	(void)p2;
	(void)p3;
	load_param(sp, p1, 1);
	ft_printf("%c", swap32(memory_tou32(p1)));
}
