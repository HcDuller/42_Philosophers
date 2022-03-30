/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:45:18 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 20:57:10 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static int	eat_action(t_philo *philosopher);
static int	sleep_action(t_philo *philosopher);
static int	think_action(t_philo *philosopher);
static void	chained_actions(t_philo *philosopher);
static int	alive_and_hungry(t_philo *philosopher);

void	start_philosopher(t_philo *philosopher)
{
	pthread_t	watcher_t;

	pthread_mutex_init(&philosopher->self_lock, NULL);
	pthread_create(&watcher_t, NULL, &watcher, (void *) philosopher);
	while (alive_and_hungry(philosopher))
	{
		chained_actions(philosopher);
	}
	pthread_join(watcher_t, NULL);
	pthread_mutex_destroy(&philosopher->self_lock);
	forked_cleanup(philosopher);
	exit(EXIT_SUCCESS);
}

static void	chained_actions(t_philo *philosopher)
{
	int	keep_going;
	int (*fnc[5])(t_philo *);

	fnc[0] = pick_forks;
	fnc[1] = eat_action;
	fnc[2] = release_forks;
	fnc[3] = sleep_action;
	fnc[4] = think_action;
	keep_going = 1;
	while (keep_going != 0 && keep_going < 6)
	{
		if (fnc[keep_going -1](philosopher))
			keep_going++;
		else
			keep_going = 0;
	}
}

static int	alive_and_hungry(t_philo *philosopher)
{
	int	meals;
	int	alive;
	int simulation;

	pthread_mutex_lock(&philosopher->self_lock);
	alive = philosopher->alive;
	meals = philosopher->meals_left > 0 || philosopher->meals_left == -1;
	simulation = simulation_is_running(philosopher);
	pthread_mutex_unlock(&philosopher->self_lock);
	return (alive && meals && simulation);
}

static int	eat_action(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;

	msg = "%06ld	%02d	is eating\n";
	if (philo_alive(philosopher) && simulation_is_running(philosopher))
	{
		ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
		pthread_mutex_lock(&philosopher->self_lock);
		if (philosopher->meals_left > 0)
			philosopher->meals_left -= 1;
		gettimeofday(&philosopher->last_meal, NULL);
		pthread_mutex_unlock(&philosopher->self_lock);
		printf(msg, ellapsed_time, philosopher->p_number);
		usleep(philosopher->table->eat_time_ms * 1000);
		return (1);
	}
	return (0);
}

static int	sleep_action(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;

	msg = "%06ld	%02d	is sleeping\n";
	if (philo_alive(philosopher) && simulation_is_running(philosopher))
	{
		ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
		printf(msg, ellapsed_time, philosopher->p_number);
		usleep(philosopher->table->sleep_time_ms * 1000);
		return (1);
	}
	ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
	printf("%06ld	%02d	skiped sleeping\n", ellapsed_time, philosopher->p_number);
	return (0);
}

static int	think_action(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;

	msg = "%06ld	%02d	is thinking\n";
	if (philo_alive(philosopher) && simulation_is_running(philosopher))
	{
		ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
		printf(msg, ellapsed_time, philosopher->p_number);
		usleep(500);
		return (1);
	}
	ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
	printf("%06ld	%02d	skiped thinking\n", ellapsed_time, philosopher->p_number);
	return (0);
}
