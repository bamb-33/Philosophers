/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:17:25 by naadou            #+#    #+#             */
/*   Updated: 2024/03/04 13:09:00 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_put(char *p, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] || s2[j])
	{
		if (s1[i])
		{
			p[i + j] = s1[i];
			i++;
		}
		else
		{
			p[i + j] = s2[j];
			j++;
		}
	}
	p[i + j] = 0;
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// if (!s1 && !s2)
	// 	return (NULL);
	// if (!s1)
	// 	return (ft_strdup(s2));
	// if (!s2)
	// 	return (ft_strdup(s1));
	p = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	return (ft_put(p, s1, s2));
}
