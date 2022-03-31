/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_lock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:51:56 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 23:14:43 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	try_lock(pthread_mutex_t *mutex, t_table *table)
{
	while (mutex->__align == 1)
	{
		if (dinner_is_over(table))
			return (0);
		usleep(100);
	}
	pthread_mutex_lock(mutex);
	return (1);
}
