/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:16:42 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/28 19:44:30 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static	void	set_up_table(t_table *table, int argc, unsigned int	*args);
static	void	set_up_semaphores(t_table *table, unsigned int	*args);
static	void	init_philosophers(t_table *table);

void	set_up_dinner(t_table *table, int argc, unsigned int	*args)
{
	set_up_semaphores(table, args);
	set_up_table(table, argc, args);
	table->philosophers = ft_calloc(args[0], sizeof(t_philo));
}

static	void	init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philosopher;

	i = 0;
	while (i < table->n_philosophers)
	{
		philosopher = table->philosophers + i;
		ft_bzero(philosopher, sizeof(philosopher));
		philosopher->table = table;
		philosopher->last_meal = table->base_time;
		philosopher->pid = fork();
		if (philosopher->pid == 0)
		{
			
		}
		i++;
	}
}

static	void	set_up_semaphores(t_table *table, unsigned int	*args)
{
	sem_unlink("/forks");
	table->forks = sem_open("/forks", O_CREAT,  S_IRUSR | S_IWUSR, (int) args[0]);
	sem_unlink("/philos_alive");
	table->philosophers_are_alive = sem_open("/philos_alive", O_CREAT,S_IRUSR | S_IWUSR, 1);
	sem_unlink("/philos_dead");
	table->a_philo_died = sem_open("/philos_dead", O_CREAT,S_IRUSR | S_IWUSR, 0);
}

static	void	set_up_table(t_table *table, int argc, unsigned int	*args)
{
	if (gettimeofday(&table->base_time, NULL))
		exit(EXIT_FAILURE);
	table->starv_time_ms = args[1];
	table->eat_time_ms = args[2];
	table->sleep_time_ms = args[3];
	table->meals = args[4];
}
