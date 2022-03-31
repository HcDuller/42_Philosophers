/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:58:10 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 23:18:02 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	philosopher_life(t_philo *philosopher);

void	*phi_thread(void *arg)
{
	t_philo	*philosopher;
	int		meals_left;

	philosopher = (t_philo *)arg;
	while (!dinner_is_over(philosopher->table))
	{
		pthread_mutex_lock(&philosopher->self_lock);
		meals_left = philosopher->meals_left;
		pthread_mutex_unlock(&philosopher->self_lock);
		if (meals_left == 0)
		{
			return (NULL);
		}
		else if (meals_left != 0)
		{
			if (!philosopher_life(philosopher))
			{
				return (NULL);
			}
		}
	}
	return (NULL);
}

static int	philosopher_life(t_philo *philosopher)
{
	int	(*fnc[5])(t_philo *);
	int	keep_going;

	fnc[0] = pick_forks;
	fnc[1] = eat_action;
	fnc[2] = release_forks;
	fnc[3] = sleep_action;
	fnc[4] = think_action;
	keep_going = 1;
	while (keep_going != 0 && keep_going < 6)
	{
		if (fnc[keep_going - 1](philosopher))
			keep_going++;
		else
			keep_going = 0;
	}
	return (keep_going != 0);
}
