/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elapsed_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:08 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 00:29:25 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<philosophers_bonus.h>

unsigned long int	get_elapsed_ms(struct timeval *base_time)
{
	struct timeval		now;
	unsigned long int	sec;
	unsigned long int	usec;

	if (gettimeofday(&now, NULL))
		exit(EXIT_FAILURE);
	sec = (now.tv_sec - base_time->tv_sec) * 1000;
	usec = (now.tv_usec - base_time->tv_usec) / 1000;
	return (sec + usec);
}
