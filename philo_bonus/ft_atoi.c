/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:32:02 by naadou            #+#    #+#             */
/*   Updated: 2024/03/09 19:30:12 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_atoi(const char *str, t_to_free *head)
{
	int	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	if (*str == '\0')
	{
		printf("one of the argument is not valid\n");
		ft_lstclear(head);
		exit(1);
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - 48);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != '\0')
	{
		printf("one of the argument is not valid\n");
		ft_lstclear(head);
		exit(1);
	}
	return (result);
}
