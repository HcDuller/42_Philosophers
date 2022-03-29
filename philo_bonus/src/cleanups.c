/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:02:20 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 16:03:09 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	clean_up(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
}

void	forked_cleanup(t_philo *philosopher)
{
	t_table			*table;
	t_philo			*tmp_philo;
	unsigned int	p;

	table = philosopher->table;
	p = 0;
	while (p < table->n_philosophers &&  table->philosophers + p < philosopher)
	{
		tmp_philo = table->philosophers + p;
		pthread_mutex_destroy(&tmp_philo->self_lock);
		p++;
	}
	pthread_mutex_destroy(&philosopher->self_lock);
	free(table->philosophers);
}