/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:14 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/21 21:18:38 by hde-camp         ###   ########.fr       */
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

typedef	struct s_philo
{
	pthread_t		thread;
	int				vector_id;
	char			*str_id;
	struct	timeval	base_time;
	struct	timeval	last_meal;
	unsigned int	starv_time_ms;
	unsigned int	sleep_time_ms;
	unsigned int	eat_time_ms;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	self_lock;
} t_philo;

typedef struct s_table
{
	int					n_philosophers;
	int					thread_counter;
	pthread_mutex_t		self_lock;
	pthread_mutex_t		*forks;
	t_philo				*philosophers;
	struct	timeval		base_time;
} t_table;

char			*ft_itoa(int n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned long	get_elapsed_ms(struct timeval *base_time);
#endif
