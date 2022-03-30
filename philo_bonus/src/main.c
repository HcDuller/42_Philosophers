/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:57:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 17:10:54 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	*watcher(void *arg)
{
	t_table	*table;

	table = arg;
	while (1)
	{
		if(starved_to_death(table))
		{
			break;
		}
		if (!simulating(table))
		{
			break;
		}
	}
	return (NULL);
}

void	start_philosopher(t_philo	*philosopher)
{
	int	t;
	pthread_t	watcher_t;

	t = 1;
	if (pthread_create(&watcher_t, NULL, watcher, philosopher->table))
	{
		perror("Error when creating watcher:");
		undo_child_table(philosopher->table);
	}
	while (t)
	{
		t = pick_forks(philosopher->table);
		if (t)
		{
			t = philo_eat(philosopher->table);
		}
		if (t)
		{
			t = release_forks(philosopher->table);
		}
		if (t)
		{
			t = philo_sleep(philosopher->table);
		}
		if (t)
		{
			t = philo_think(philosopher->table);
		}
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
