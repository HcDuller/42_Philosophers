/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:57:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/28 19:19:39 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	main(int argc, char *argv[])
{
	unsigned int	args[5];
	t_table			table;

	eval_input(argc, argv);
	parse_params(argc, argv + 1, args);
	if (args[0])
	{
		set_up_dinner(&table, argc, args);
	}
	return (0);
}
