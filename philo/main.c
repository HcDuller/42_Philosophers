/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:47:57 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/21 20:32:18 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/*
	1000 microsecond = 1 milisecond
*/

void	validate_argc(int	argc)
{
	if (argc < 5)
	{
		write(STDIN_FILENO,"Too few arguments\n", 18);
		exit(EXIT_FAILURE);
	}
	else if (argc > 6)
	{
		write(STDIN_FILENO,"Too many arguments\n", 19);
		exit(EXIT_FAILURE);
	}
}

int	is_digit(int	c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	validate_argv(char **argv)
{
	int	i;
	int	c_i;

	i = 1;
	while (argv[i])
	{
		c_i = 0;
		while (argv[i][c_i])
		{
			if (!is_digit(argv[i][c_i]))
			{
				write(STDERR_FILENO, "Only numeric ", 13);
				write(STDERR_FILENO, "parameters are allowed\n", 23);
				exit(EXIT_FAILURE);
			}
			c_i++;
		}
		i++;
	}
}

unsigned int	str_to_uint(char *str)
{
	int	i;
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

void	parse_params(int	argc, char *argv[], unsigned int	*i_args)
{
	unsigned int	i;
	unsigned int	u_argc;

	u_argc = (unsigned int)argc - 1;
	ft_bzero(i_args, 5 * sizeof(unsigned int));
	i = 0;
	while(i < u_argc)
	{
		i_args[i] = str_to_uint(*(argv + i));
		i++;
	}
}

void	alloc_table(t_table	*table, unsigned int *args)
{
	int	p_count;

	table->n_philosophers = args[0];
	table->forks = ft_calloc(args[0], sizeof(pthread_mutex_t));
	table->philosophers = ft_calloc(args[0], sizeof(t_philo));
	gettimeofday(&(table->base_time), NULL);
	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		(table->philosophers + p_count)->starv_time_ms = args[1];
		(table->philosophers + p_count)->eat_time_ms = args[2];
		(table->philosophers + p_count)->sleep_time_ms = args[3];
		if (pthread_mutex_init( table->forks + p_count, NULL))
		{
			write(STDERR_FILENO, "Error: could not create mutex.\n", 31);
			exit(EXIT_FAILURE);
		}
		p_count++;
	}
}

void	free_table(t_table *table)
{
	int	p_count;

	p_count = 0;
	free(table->philosophers);
	while (p_count < table->n_philosophers)
	{
		pthread_mutex_destroy(table->forks + p_count);
		p_count++;
	}
	free(table->forks);
}

void	pick_forks(t_philo	*philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	printf("%08ld	[%02d]	has taken a fork(left)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id);
	pthread_mutex_lock(philosopher->right_fork);
	printf("%08ld	[%02d]	has taken a fork(right)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id);
}

void	release_forks(t_philo	*philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	printf("%08ld	[%02d]	released a fork(left)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id);
	pthread_mutex_unlock(philosopher->right_fork);
	printf("%08ld	[%02d]	released a fork(right)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id);
}

void	eat_action(t_philo	*philosopher)
{
	unsigned long	eat_time;

	eat_time = get_elapsed_ms(&(philosopher->base_time));
	printf("%08ld	[%02d]	is eating\n", eat_time, philosopher->vector_id);
	gettimeofday(&philosopher->last_meal, NULL);
	usleep(1000 * philosopher->eat_time_ms);
}

void	sleep_action(t_philo	*philosopher)
{
	printf("%08ld	[%02d]	is sleeping\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id);
	usleep(1000 * philosopher->sleep_time_ms);
}

void	*phi_thread(void *arg)
{
	t_philo	*philosopher;
	
	philosopher = arg;
	while (1)
	{
		pthread_mutex_lock(&philosopher->self_lock);
		pick_forks(philosopher);
		eat_action(philosopher);
		pthread_mutex_unlock(&philosopher->self_lock);
		release_forks(philosopher);
		sleep_action(philosopher);
	}
	return (NULL);
}

void	start_philosophers(t_table *table)
{
	int		p_count;
	t_philo	*philo;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		philo = table->philosophers + p_count;
		philo->vector_id = p_count;
		philo->str_id = ft_itoa(p_count);
		philo->left_fork = table->forks + p_count;
		philo->last_meal = table->base_time;
		philo->base_time = table->base_time;
		if (pthread_mutex_init(&philo->self_lock, NULL))
			exit(EXIT_FAILURE);
		if (p_count + 1 == table->n_philosophers)
			philo->right_fork = table->forks;
		else
			philo->right_fork = table->forks + p_count + 1;
		p_count++;
	}
	if (pthread_create(&(table->philosophers->thread), NULL, &phi_thread, (void *) table->philosophers))
		exit(EXIT_FAILURE);
	usleep(1000);
	p_count = 1;
	while (p_count < table->n_philosophers)
	{
		philo = table->philosophers + p_count;
		if (pthread_create(&(philo->thread), NULL, &phi_thread, (void *) philo))
			exit(EXIT_FAILURE);
		p_count++;
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

void	check_starvation(t_philo	*philosopher)
{
	unsigned long int	elapsed_meal_time;
	unsigned long int	elapsed_base_time;

	pthread_mutex_lock(&philosopher->self_lock);
	elapsed_meal_time = get_elapsed_ms(&philosopher->last_meal);
	elapsed_base_time = get_elapsed_ms(&(philosopher->base_time));
	pthread_mutex_unlock(&philosopher->self_lock);
	if (elapsed_meal_time > philosopher->starv_time_ms)
	{
		printf("%08ld	[%02d]	(starved for %08ldms) died\n", elapsed_base_time, philosopher->vector_id, elapsed_meal_time);
		exit(EXIT_FAILURE);
	}
}

void	*overwatcher(void	*arg)
{
	t_table	*table;
	int		p_counter;

	table = (t_table *)arg;
	while (1)
	{
		p_counter = 0;
		while (p_counter < table->n_philosophers)
		{
			check_starvation(table->philosophers + p_counter);
			p_counter++;
		}
	}
	return (NULL);
}

void	start_watcher(t_table	*table)
{
	pthread_t	watcher;

	if(pthread_create(&watcher,NULL, &overwatcher, (void *)table))
	{
		write(STDERR_FILENO,"Could not create overwatcher.\n",30);
		exit(EXIT_FAILURE);
	}
}

int	main(int	argc, char	*argv[])
{
	unsigned int	args[5];
	t_table			table;

	validate_argc(argc);
	validate_argv(argv);
	parse_params(argc, argv + 1, args);
	alloc_table(&table, args);
	start_philosophers(&table);
	start_watcher(&table);
	wait_philosophers(&table);
	free_table(&table);
	return (0);
}