/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 20:07:21 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstprev(t_list *first, t_list *node)
{
	t_list	*prev;

	if (!first || !node || first == node)
		return (NULL);
	prev = first;
	while (prev)
	{
		if (prev->next == node)
			return (prev);
		prev = prev->next;
	}
	return (NULL);
}
