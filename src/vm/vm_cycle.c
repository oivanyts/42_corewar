/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:19:07 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:19:08 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vs.h"

uint32_t	threads_alive(t_threads *threads)
{
	size_t		thread;
	uint32_t	alive;

	alive = 0;
	thread = 0;
	while (thread < threads_size(threads))
	{
		if (threads_at(threads, thread)->alive)
		{
			alive += threads_at(threads, thread)->lives;
		}
		++thread;
	}
	return (alive);
}

void		kill_thread_if_no_lives(t_thread *th)
{
	if ((int32_t)(get_vm(0)->cycle - th->last_live) >= get_vm(0)->ctd
	&& th->alive)
	{
		th->alive = 0;
		get_vm(0)->options.o_v_param & 8 ?
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				th - threads_at(&get_vm(0)->threads, 0) + 1,
				get_vm(0)->cycle - th->last_live, get_vm(0)->ctd) : 0;
	}
	else
	{
		th->lives = 0;
	}
}

void		foreach_thread(t_threads *threads, void (*func)(t_thread *))
{
	int32_t	thread;

	thread = threads_size(threads) - 1;
	while (thread >= 0)
	{
		func(threads_at(threads, thread));
		--thread;
	}
}

void		ctd_check(t_vm *vm, int32_t *cycles, uint32_t *checks,
		uint32_t *alive)
{
	if (*cycles >= vm->ctd)
	{
		*alive = threads_alive(&vm->threads);
		foreach_thread(&vm->threads, kill_thread_if_no_lives);
		*cycles = 0;
		ft_resetlivesinper(vm);
		++*checks;
		if (*alive >= NBR_LIVE)
		{
			vm->ctd -= CYCLE_DELTA;
			!vm->options.visual_ncurses && (vm->options.o_v_param & 2)
			? ft_printf("Cycle to die is now %d\n", vm->ctd) : 0;
			*checks = 0;
		}
	}
	if (*checks == MAX_CHECKS)
	{
		vm->ctd -= CYCLE_DELTA;
		!vm->options.visual_ncurses && (vm->options.o_v_param & 2)
		? ft_printf("Cycle to die is now %d\n", vm->ctd) : 0;
		*checks = 0;
	}
}

void		vm_cycle(t_vm *vm)
{
	int32_t		cycles;
	uint32_t	checks;
	uint32_t	alive;

	cycles = 1;
	vm->ctd = CYCLE_TO_DIE;
	checks = 0;
	alive = 1;
	while (alive)
	{
		!vm->options.visual_ncurses && (vm->options.o_v_param & 2)
		? ft_printf("It is now cycle %d\n", vm->cycle, vm->ctd, cycles) : 0;
		foreach_thread(&vm->threads, op_exec);
		ctd_check(vm, &cycles, &checks, &alive);
		if (vm->cycle == vm->options.o_dump_point && vm->options.o_dump)
		{
			poor_mans_visualization(threads_at(&vm->threads, 0)->vm_memory);
			return ;
		}
		vm->options.visual_ncurses ? ft_drawmap(vm) : 0;
		++cycles;
		++vm->cycle;
	}
}
