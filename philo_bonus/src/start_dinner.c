/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:00:07 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/28 20:23:56 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>


void	start_dinner(t_table *table)
{
	int		proc_c;
	t_philo	*philosopher;

	proc_c = 0;
	while (proc_c < table->n_philosophers)
	{
		philosopher = table->philosophers + proc_c;
		proc_c++;
	}
}
