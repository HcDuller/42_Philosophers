/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:52:25 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/17 18:58:18 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static	int	r_len(int n);
static	int	mod(int n);

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*p;

	len = r_len(n);
	i = len;
	p = ft_calloc(i + 1, 1);
	if (!p)
		return (NULL);
	while (i > 0)
	{
		p[--i] = mod(n % 10) + 48;
		if (!(n / 10 == 0))
			n = n / 10;
		else if (n < 0)
			p[--i] = 45;
	}
	return (p);
}

int	r_len(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	mod(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
