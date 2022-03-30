/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:57:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 01:23:00 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	start_philosopher(t_philo	*philosopher)
{
	printf("Philosopher %d started!\n", philosopher->p_number);
	pick_forks(philosopher->table);
	release_forks(philosopher->table);
	philo_eat(philosopher->table);
	philo_sleep(philosopher->table);
	philo_think(philosopher->table);
	undo_table(philosopher->table);
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
