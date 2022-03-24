/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:47:57 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/24 13:54:28 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

unsigned int	str_to_uint(char *str)
{
	int				i;
	unsigned int	value;
	unsigned int	pow;

	i = 0;
	value = 0;
	pow = 1;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		value += (((int) str[i]) - 48) * pow;
		i--;
		pow *= 10;
	}
	return (value);
}

void	parse_params(int argc, char *argv[], unsigned int *i_args)
{
	unsigned int	i;
	unsigned int	u_argc;

	u_argc = (unsigned int)argc - 1;
	ft_bzero(i_args, 5 * sizeof(unsigned int));
	i = 0;
	while (i < u_argc)
	{
		i_args[i] = str_to_uint(*(argv + i));
		i++;
	}
}

void	wait_philosophers(t_table	*table)
{
	int		p_count;
	t_philo	*philo;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		usleep(1000);
		philo = table->philosophers + p_count;
		if (pthread_join(philo->thread, NULL))
			exit(EXIT_FAILURE);
		p_count++;
	}
}

int	main(int argc, char *argv[])
{
	unsigned int	args[5];
	t_table			table;

	eval_input(argc, argv);
	parse_params(argc, argv + 1, args);
	alloc_table(&table, argc, args);
	start_philosophers(&table);
	start_watcher(&table);
	wait_philosophers(&table);
	free_table(&table);
	return (0);
}
