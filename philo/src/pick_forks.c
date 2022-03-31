/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:16:22 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 23:27:19 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	pick_right_fork(t_philo *philosopher);
static int	pick_left_fork(t_philo *philosopher);

int	pick_forks(t_philo	*philosopher)
{
	if (philosopher->vector_id % 2)
	{
		if (pick_left_fork(philosopher))
		{
			if (pick_right_fork(philosopher))
				return (1);
		}
	}
	else
	{
		if (pick_right_fork(philosopher))
		{
			if (pick_left_fork(philosopher))
				return (1);
		}
	}
	return (0);
}

static	int	pick_right_fork(t_philo *philosopher)
{
	int				id;
	unsigned long	p_time;

	if (try_lock(philosopher->right_fork, philosopher->table))
	{
		id = philosopher->vector_id + 1;
		p_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%06ld	%02d	has taken a fork(right)\n", p_time, id);
		return (1);
	}
	return (0);
}

static	int	pick_left_fork(t_philo *philosopher)
{
	int				id;
	unsigned long	p_time;

	if (try_lock(philosopher->left_fork, philosopher->table))
	{
		id = philosopher->vector_id + 1;
		p_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%06ld	%02d	has taken a fork(left)\n", p_time, id);
		return (1);
	}
	return (0);
}
