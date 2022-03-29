/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:45:18 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 13:47:16 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static void	eat_action(t_philo *philosopher);
static void	sleep_action(t_philo *philosopher);
static void	think_action(t_philo *philosopher);
static void	release_forks(t_philo *philosopher);
static void	pick_forks(t_philo *philosopher);

void	start_philosopher(t_philo *philosopher)
{
	int			*meals;
	pthread_t	watcher_t;

	meals = &philosopher->meals_left;
	pthread_mutex_init(&philosopher->self_lock, NULL);
	pthread_create(&watcher_t, NULL, &watcher, (void *) philosopher);
	while (*meals > 0 || *meals == -1)
	{
		pick_forks(philosopher);
		eat_action(philosopher);
		release_forks(philosopher);
		sleep_action(philosopher);
		think_action(philosopher);
	}
	pthread_join(watcher_t, NULL);
	pthread_mutex_destroy(&philosopher->self_lock);
	exit(EXIT_SUCCESS);
}

static void	release_forks(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;
	t_table			*table;

	msg = "%06ld	%02d	has released a fork\n";
	table = philosopher->table;
	sem_post(table->forks);
	ellapsed_time = get_elapsed_ms(&table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
	sem_post(table->forks);
	ellapsed_time = get_elapsed_ms(&table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
}

static void	pick_forks(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	t_table			*table;
	char			*msg;

	table = philosopher->table;
	msg = "%06ld	%02d	has taken a fork\n";
	sem_wait(table->forks);
	ellapsed_time = get_elapsed_ms(&table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
	sem_wait(table->forks);
	ellapsed_time = get_elapsed_ms(&table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
}

static void	eat_action(t_philo *philosopher)
{
	unsigned long	ellapsed_time;

	pthread_mutex_lock(&philosopher->self_lock);
	if (philosopher->meals_left > 0)
		philosopher->meals_left -= 1;
	ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
	gettimeofday(&philosopher->last_meal, NULL);
	pthread_mutex_unlock(&philosopher->self_lock);
	printf("%06ld	%02d	is eating\n", ellapsed_time, philosopher->p_number);
	usleep(philosopher->table->eat_time_ms * 1000);
}

static void	sleep_action(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;

	msg = "%06ld	%02d	is sleeping\n";
	ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
	usleep(philosopher->table->sleep_time_ms * 1000);
}

static void	think_action(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;

	msg = "%06ld	%02d	is thinking\n";
	ellapsed_time = get_elapsed_ms(&philosopher->table->base_time);
	printf(msg, ellapsed_time, philosopher->p_number);
	usleep(100);
}
