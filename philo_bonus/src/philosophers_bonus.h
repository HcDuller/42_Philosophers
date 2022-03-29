/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:18:15 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 16:37:36 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_table
{
	sem_t			*forks;
	sem_t			*a_philo_died;
	sem_t			*print_lock;
	t_philo			*philosophers;
	struct timeval	base_time;
	int				meals;
	unsigned int	n_philosophers;
	unsigned int	starv_time_ms;
	unsigned int	sleep_time_ms;
	unsigned int	eat_time_ms;
};

struct s_philo
{
	pid_t			pid;
	int				p_number;
	int				e_code;
	int				alive;
	int				meals_left;
	struct timeval	last_meal;
	pthread_mutex_t	self_lock;
	t_table			*table;
};

# define C_RESET "\033[0m"
# define C_RED "\033[31m"
# define C_GREEN "\033[32m"
# define C_YELLOW "\033[33m"
# define C_BLUE "\033[34m"
# define C_MAGENTA "\033[35m"
# define C_CYAN "\033[36m"
# define C_WHITE "\033[37m"

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				eval_input(int argc, char **argv);
void				parse_params(int argc, char *argv[], unsigned int *i_args);
void				set_up_dinner(t_table *table, unsigned int	*args);
unsigned long int	get_elapsed_ms(struct timeval *base_time);
void				start_dinner(t_table *table);
void				start_philosopher(t_philo *philosopher);
void				*watcher(void *arg);
int					release_forks(t_philo *philosopher);
int					pick_forks(t_philo *philosopher);
void				forked_cleanup(t_philo *philosopher);
void				clean_up(t_table *table);
#endif