/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:14 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/23 16:31:09 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# define C_RESET "\033[0m"
# define C_RED "\033[31m"
# define C_GREEN "\033[32m"
# define C_YELLOW "\033[33m"
# define C_BLUE "\033[34m"
# define C_MAGENTA "\033[35m"
# define C_CYAN "\033[36m"
# define C_WHITE "\033[37m"

typedef struct s_philo
{
	pthread_t		thread;
	int				vector_id;
	int				meals_left;
	struct timeval	base_time;
	struct timeval	last_meal;
	unsigned int	starv_time_ms;
	unsigned int	sleep_time_ms;
	unsigned int	eat_time_ms;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	self_lock;
}	t_philo;

typedef struct s_table
{
	int					n_philosophers;
	int					thread_counter;
	int					still_dining;
	pthread_mutex_t		self_lock;
	pthread_mutex_t		*forks;
	t_philo				*philosophers;
	struct timeval		base_time;
}	t_table;

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned long	get_elapsed_ms(struct timeval *base_time);
void			eat_action(t_philo	*philosopher);
void			sleep_action(t_philo	*philosopher);
void			think_action(t_philo	*philosopher);
void			start_philosophers(t_table *table);
int				philosophers_are_dinning(t_table	*table);
void			*phi_thread(void *arg);
void			eval_input(int argc, char **argv);
void			start_watcher(t_table	*table);
#endif
