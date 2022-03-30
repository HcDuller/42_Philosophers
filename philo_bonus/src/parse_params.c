/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:31:24 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 23:12:44 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static unsigned int	str_to_uint(char *str);

void	parse_params(int argc, char *argv[], unsigned int *i_args)
{
	unsigned int	i;
	unsigned int	u_argc;

	u_argc = (unsigned int)argc - 1;
	ft_bzero(i_args, 5 * sizeof(unsigned int));
	i = 0;
	while (i < u_argc)
	{
		i_args[i] = str_to_uint(*(argv + i));
		i++;
	}
	if (argc == 5)
		i_args[4] = -1;
}

static unsigned int	str_to_uint(char *str)
{
	int				i;
	unsigned int	value;
	unsigned int	pow;

	i = 0;
	value = 0;
	pow = 1;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		value += (((int) str[i]) - 48) * pow;
		i--;
		pow *= 10;
	}
	return (value);
}






