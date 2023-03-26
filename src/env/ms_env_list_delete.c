/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 12:19:32 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_list_delete(t_list **env_list, t_list *node)
{
	t_list	*prev;

	if (!env_list || !*env_list || !node)
		return ;
	prev = ft_lstprev(*env_list, node);
	if (prev)
		prev->next = node->next;
	else
		*env_list = node->next;
	ft_lstdelone(node, ms_env_delete);
}
