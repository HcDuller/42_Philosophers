/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:16:22 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/31 14:21:19 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	pick_right_fork(t_philo *philosopher);
static int	pick_left_fork(t_philo *philosopher);
static int	is_my_time(t_philo *philosopher);
static void	set_next_to_dine(t_philo *philosopher);

int	pick_forks(t_philo	*philosopher)
{
	while (!is_my_time(philosopher))
	{
		if (dinner_is_over(philosopher->table))
			return (0);
		usleep(100);
	}
	if (pick_right_fork(philosopher))
	{
		if (pick_left_fork(philosopher))
		{
			set_next_to_dine(philosopher);
			return (1);
		}
	}
	return (0);
}

static	int	pick_right_fork(t_philo *philosopher)
{
	if (try_lock(philosopher->right_fork, philosopher->table))
	{
		print_msg("%06ld	%02d	has taken a fork(right)\n", philosopher);
		return (1);
	}
	return (0);
}

static	int	pick_left_fork(t_philo *philosopher)
{
	if (try_lock(philosopher->left_fork, philosopher->table))
	{
		print_msg("%06ld	%02d	has taken a fork(left)\n", philosopher);
		return (1);
	}
	return (0);
}

static int	is_my_time(t_philo *philosopher)
{
	t_table	*table;
	int		allowed;

	table = philosopher->table;
	if (try_lock(&table->self_lock, table))
	{
		allowed = table->allowed_to_dine;
		pthread_mutex_unlock(&table->self_lock);
		return (allowed == philosopher->vector_id);
	}
	return (0);
}

static void	set_next_to_dine(t_philo *philosopher)
{
	int		next;

	next = get_next_in_line(philosopher);
	if (try_lock(&philosopher->table->self_lock, philosopher->table))
	{
		philosopher->table->allowed_to_dine = next;
		pthread_mutex_unlock(&philosopher->table->self_lock);
	}
}
