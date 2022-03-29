/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:57:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 16:17:27 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	wait_dinner_end(t_table *table)
{
	unsigned int	id;
	t_philo			*philosopher;

	id = 0;
	while (id < table->n_philosophers)
	{
		philosopher = table->philosophers + id;
		waitpid(philosopher->pid, &philosopher->e_code, 0);
		printf("philosopher %d proc ended\n",philosopher->p_number);
		id++;
	}
}

int	main(int argc, char *argv[])
{
	unsigned int	args[5];
	t_table			table;

	eval_input(argc, argv);
	parse_params(argc, argv + 1, args);
	if (args[0])
	{
		ft_bzero(&table, sizeof(t_table));
		set_up_dinner(&table, args);
		start_dinner(&table);
		wait_dinner_end(&table);
		clean_up(&table);
	}
	return (0);
}
