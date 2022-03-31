/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:18:12 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 21:38:07 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	fork_avalability(t_table *table, int n)
{
	int	is_available;

	if (try_wait(table->fork_lock, table))
	{
		is_available = table->forks->__align >= n;
		sem_post(table->fork_lock);
		return (is_available);
	}
	else
		return (0);
}

int	pick_a_fork(t_table	*table)
{
	int	ret;

	if (try_wait(table->fork_lock, table))
	{
		ret = try_wait(table->forks, table);
		sem_post(table->fork_lock);
		if (ret)
			print_msg("%06ld	%02d	has taken a fork\n", table);
		return (ret);
	}
	return (0);
}

int	pick_forks(t_table	*table)
{
	if (simulating(table) && is_alive(table))
	{
		if (try_wait(table->hands_lock, table))
		{
			if (pick_a_fork(table))
			{
				if (pick_a_fork(table))
				{
					sem_post(table->hands_lock);
					return (1);
				}
			}
			sem_post(table->hands_lock);
			return (0);
		}
	}
	return (0);
}

int	release_forks(t_table	*table)
{
	if (simulating(table) && is_alive(table))
	{
		sem_post(table->forks);
		print_msg("%06ld	%02d	has released a fork\n", table);
		sem_post(table->forks);
		print_msg("%06ld	%02d	has released a fork\n", table);
		return (1);
	}
	return (0);
}
