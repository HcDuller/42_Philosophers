/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:45:18 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/28 20:26:11 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	eat_action(t_philo *philosopher)
{
	gettimeofday(&philosopher->last_meal, NULL);
	printf("Philosopher %d is eating\n",philosopher->p_number);
	usleep(philosopher->table->eat_time_ms * 1000);
}

void	sleep_action(t_philo *philosopher)
{
	printf("Philosopher %d is sleeping\n",philosopher->p_number);
	usleep(philosopher->table->sleep_time_ms * 1000);
}

void	think_action(t_philo *philosopher)
{
	printf("Philosopher %d is thinking\n",philosopher->p_number);
	usleep(1000);
}

void	start_philosopher(t_philo *philosopher)
{
	int	meals;

	meals = philosopher->table->meals;

	while (meals > 0 || meals == -1)
	{
	}
}
