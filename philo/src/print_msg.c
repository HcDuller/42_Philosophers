/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:28:10 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/31 12:35:59 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_msg(char *msg, t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	t_table			*table;

	table = philosopher->table;
	ellapsed_time = get_elapsed_ms(&table->base_time);
	printf(msg, ellapsed_time, philosopher->vector_id + 1);
}
