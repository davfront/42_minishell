/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 10:48:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_list_set(t_list **env_list, char *label, char *value)
{
	t_list	*node;
	t_env	*env;

	if (!env_list || !label)
		return ;
	if (!ms_env_is_valid_identifier(label))
		return ;
	node = ms_env_list_get_by_label(*env_list, label);
	if (node)
		ms_env_list_update(node, value);
	else
	{
		env = ms_env_new(label, value);
		// todo: protect malloc
		ms_env_list_add(env_list, label, value);
	}
}
