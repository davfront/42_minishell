/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:40:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_list_set(t_list **env_list, char *label, char *value, int export)
{
	t_list	*node;
	t_env	*env;

	if (!env_list || !label)
		return (FAILURE);
	if (!ms_env_is_valid_identifier(label))
		return (FAILURE);
	node = ms_env_list_find(*env_list, label);
	if (node)
		return (ms_env_list_update(node, value, export));
	else
	{
		env = ms_env_new(label, value, export);
		if (!env)
			return (FAILURE);
		return (ms_env_list_add(env_list, env));
	}
}
