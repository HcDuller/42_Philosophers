/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:33:48 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 15:16:29 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	print_msg(char *msg, t_table *table)
{
	unsigned long	ellapsed_time;

	pthread_mutex_lock(&table->philosopher.self_lock);
	ellapsed_time = get_elapsed_ms(&table->base_time);
	pthread_mutex_unlock(&table->philosopher.self_lock);
	printf(msg, ellapsed_time, table->philosopher.p_number);
}