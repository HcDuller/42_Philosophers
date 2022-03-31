/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:57:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 23:58:41 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	*watcher(void *arg)
{
	t_table	*table;

	table = arg;
	while (!is_full(table))
	{
		if (starved_to_death(table))
		{
			break ;
		}
		if (!simulating(table))
		{
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void	philo_chain(t_table *table)
{
	int	(*fnc[5])(t_table *);
	int	keep_going;

	fnc[0] = pick_forks;
	fnc[1] = philo_eat;
	fnc[2] = release_forks;
	fnc[3] = philo_sleep;
	fnc[4] = philo_think;
	keep_going = 1;
	while (keep_going != 0 && keep_going < 6)
	{
		if (fnc[keep_going - 1](table))
			keep_going++;
		else
			keep_going = 0;
	}
}

void	start_philosopher(t_philo	*philosopher)
{
	pthread_t	watcher_t;

	if (pthread_create(&watcher_t, NULL, watcher, philosopher->table))
	{
		perror("Error when creating watcher:");
		undo_child_table(philosopher->table);
	}
	while (!is_full(philosopher->table) && simulating(philosopher->table))
	{
		philo_chain(philosopher->table);
	}
	if (pthread_join(watcher_t, NULL))
		perror("pthread error:");
	undo_child_table(philosopher->table);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	unsigned int	args[5];
	t_table			table;

	eval_input(argc, argv);
	parse_params(argc, argv + 1, args);
	if (args[0])
	{
		set_up_table(&table, args);
		start_dinner(&table);
		wait_dinner_end(&table);
		undo_table(&table);
	}
	return (0);
}
