/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:08:37 by evallee-          #+#    #+#             */
/*   Updated: 2023/07/19 16:10:50 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long		m;
	long		num;

	if (!str)
		return (0);
	m = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			m *= -1;
	}
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	return (num * m);
}
