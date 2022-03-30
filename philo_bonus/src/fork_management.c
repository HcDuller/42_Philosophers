/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:18:12 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 13:12:05 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	fork_avalability(t_table	*table, int	n)
{
	int	is_available;

	sem_wait(table->fork_lock);
	is_available = table->forks->__align >= n;
	sem_post(table->fork_lock);
	return (is_available);
}

int	pick_a_fork(t_table	*table)
{
	sem_wait(table->fork_lock);
	sem_wait(table->forks);
	sem_post(table->fork_lock);
	print_msg("%06ld	%02d	has taken a fork\n", table);
	return (1);
}

int	pick_forks(t_table	*table)
{
	while (!fork_avalability(table, 2))
		usleep(100);
	pick_a_fork(table);
	pick_a_fork(table);
	return (1);
}

int	release_forks(t_table	*table)
{
	sem_wait(table->fork_lock);
	sem_post(table->forks);
	print_msg("%06ld	%02d	has released a fork\n", table);
	sem_post(table->forks);
	print_msg("%06ld	%02d	has released a fork\n", table);
	sem_post(table->fork_lock);
	return (1);
}
