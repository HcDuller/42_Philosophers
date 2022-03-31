/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:58:15 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 21:33:59 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	try_wait(sem_t *sem, t_table *table)
{
	while (sem->__align == 0)
	{
		usleep(1000);
		if (!simulating(table))
			return (0);
	}
	sem_wait(sem);
	return (1);
}
