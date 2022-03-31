/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_is_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:07:13 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 22:09:37 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	dinner_is_over(t_table *table)
{
	int	is_over;

	pthread_mutex_lock(&table->self_lock);
	is_over = !table->still_dining;
	pthread_mutex_unlock(&table->self_lock);
	return (is_over);
}
