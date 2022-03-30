/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:30:01 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 21:41:13 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	release_a_fork(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;
	t_table			*table;

	if (philo_alive(philosopher) && simulation_is_running(philosopher))
	{
		msg = "%06ld	%02d	has released a fork\n";
		table = philosopher->table;
		ellapsed_time = get_elapsed_ms(&table->base_time);
		sem_wait(table->fork_lock);
		sem_post(table->forks);
		sem_post(table->fork_lock);
		printf(msg, ellapsed_time, philosopher->p_number);
		return (1);
	}
	return (0);
}

int	release_forks(t_philo *philosopher)
{
	if (release_a_fork(philosopher))
	{
		if (release_a_fork(philosopher))
			return (1);
	}
	return (0);
	//unsigned long	ellapsed_time;
	//char			*msg;
	//t_table			*table;
//
	//if (philo_alive(philosopher) && simulation_is_running(philosopher))
	//{
	//	msg = "%06ld	%02d	has released a fork\n";
	//	table = philosopher->table;
	//	sem_wait(table->fork_lock);
	//	sem_post(table->forks);
	//	ellapsed_time = get_elapsed_ms(&table->base_time);
	//	printf(msg, ellapsed_time, philosopher->p_number);
	//	sem_post(table->forks);
	//	sem_post(table->fork_lock);
	//	ellapsed_time = get_elapsed_ms(&table->base_time);
	//	printf(msg, ellapsed_time, philosopher->p_number);
	//	return (1);
	//}
	//return (0);
}

int	n_fork_unavailable(t_philo *philosopher, int n)
{
	int	availability;

	sem_wait(philosopher->table->fork_lock);
	availability = philosopher->table->forks->__align >= n;
	sem_post(philosopher->table->fork_lock);
	return (!availability);
}

void	pick_a_fork(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;

	msg = "%06ld	%02d	has taken a fork\n";
	sem_wait(philosopher->table->fork_lock);
	sem_wait(philosopher->table->forks);
	ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
	sem_post(philosopher->table->fork_lock);
}

int	try_pick_a_fork(t_philo *philosopher)
{
	while (n_fork_unavailable(philosopher, 1))
	{
		usleep(500);
	}
	if (simulation_is_running(philosopher))
	{
		pick_a_fork(philosopher);
		return (1);
	}
	return (0);
}

int	pick_forks(t_philo *philosopher)
{
	if (philo_alive(philosopher) && simulation_is_running(philosopher))
	{
		while (n_fork_unavailable(philosopher, 2) && simulation_is_running(philosopher))
		{
			usleep(100);
		}
		if (try_pick_a_fork(philosopher))
		{
			if (try_pick_a_fork(philosopher))
				return (1);
			else
			{
				release_a_fork(philosopher);
				return (pick_forks(philosopher));
			}
		}
		else
		{
			return (pick_forks(philosopher));
		}
		return (1);
	}
	return (0);
}
