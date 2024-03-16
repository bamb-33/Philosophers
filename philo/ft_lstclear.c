/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:44:33 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 20:27:34 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_lstclear(t_to_free *lst)
{
	t_to_free	*tmp;

	while (lst)
	{
		tmp = lst;
		free (tmp->content);
		lst = lst->next;
		free(tmp);
	}
}
