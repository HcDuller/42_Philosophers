/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:16:22 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/31 14:30:02 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	release_right_fork(t_philo *philosopher);
static int	release_left_fork(t_philo *philosopher);

int	release_forks(t_philo	*philosopher)
{
	if (!dinner_is_over(philosopher->table))
	{
		if (philosopher->vector_id % 2)
		{
			release_left_fork(philosopher);
			release_right_fork(philosopher);
		}
		else
		{
			release_right_fork(philosopher);
			release_left_fork(philosopher);
		}
		return (1);
	}
	return (0);
}

static int	release_right_fork(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->right_fork);
	print_msg("%06ld	%02d	released a fork(right)\n", philosopher);
	return (1);
}

static int	release_left_fork(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	print_msg("%06ld	%02d	released a fork(left)\n", philosopher);
	return (1);
}
