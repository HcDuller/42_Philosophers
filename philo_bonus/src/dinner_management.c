/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:58:46 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 21:38:35 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	start_dinner(t_table *table)
{
	unsigned int	pid_c;

	pid_c = 0;
	while (pid_c < table->n_philosophers)
	{
		(table->procs + pid_c)->p_id = fork();
		if ((table->procs + pid_c)->p_id == 0)
		{
			table->philosopher.p_number = pid_c + 1;
			start_philosopher(&table->philosopher);
		}
		pid_c++;
		usleep(100);
	}
}

void	wait_dinner_end(t_table *table)
{
	unsigned int	pid_c;
	t_proc			*proc;

	pid_c = 0;
	while (pid_c < table->n_philosophers)
	{
		proc = table->procs + pid_c;
		waitpid(proc->p_id, &proc->e_code, 0);
		pid_c++;
	}
}
