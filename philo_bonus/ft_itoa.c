/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:16:50 by naadou            #+#    #+#             */
/*   Updated: 2024/03/04 13:02:32 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	if_negative(int n, char *p)
{
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
	}
	return (n);
}

static char	*done(char *p, int num, int i)
{
	while (num > 0)
	{
		p[i] = (num % 10) + 48;
		num /= 10;
		i--;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		i;
	int		num;
	char	*p;

	i = 0;
	num = n;
	// if (n == -2147483648)
	// 	return (ft_strdup("-2147483648"));
	// if (num == 0)
	// 	return (ft_strdup("0"));
	while (num)
	{
		num /= 10;
		i++;
	}
	if (n < 0)
		i++;
	p = (char *) malloc ((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	num = if_negative(n, p);
	p[i] = 0;
	i--;
	return (done(p, num, i));
}
