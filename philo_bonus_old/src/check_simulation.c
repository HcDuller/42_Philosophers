/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:14:37 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 19:41:01 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	simulation_is_running(t_philo	*philosopher)
{
	int	running;
	sem_wait(philosopher->table->simulation_lock);
	running = philosopher->table->simulation->__align;
	sem_post(philosopher->table->simulation_lock);
	return (running);
}

int	philo_alive(t_philo	*philosopher)
{
	int	alive;

	pthread_mutex_lock(&philosopher->self_lock);
	alive = philosopher->alive;
	pthread_mutex_unlock(&philosopher->self_lock);
	return (alive);
}