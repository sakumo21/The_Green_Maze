/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:37:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/25 15:17:33 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	p;
	long	num;

	p = 1;
	num = 0;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			p *= -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	if (ft_isalpha(*nptr))
		return (-1);
	if ((p == 1 && num > 2147483647) || (p == -1 && num < -2147483648))
		return (-2);
	return (num * p);
}
