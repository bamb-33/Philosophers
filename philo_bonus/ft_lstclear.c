/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:44:33 by naadou            #+#    #+#             */
/*   Updated: 2024/02/24 10:28:21 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_lstclear(t_to_free **lst)
{
	t_to_free	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = *lst;
		free (tmp->content);
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
