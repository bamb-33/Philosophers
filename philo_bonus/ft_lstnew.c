/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:23:55 by naadou            #+#    #+#             */
/*   Updated: 2024/03/11 10:22:04 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_to_free	*ft_lstnew(void *content, t_to_free *head)
{
	t_to_free	*new_node;

	if (!content)
		return (NULL);
	new_node = (t_to_free *) w_malloc (sizeof(t_to_free), head);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
