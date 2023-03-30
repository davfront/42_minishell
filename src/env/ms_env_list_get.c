/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 12:24:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_env_list_get(t_list **env_list, char *label)
{
	t_list	*node;
	t_env	*env;

	if (!env_list || !label)
		return (NULL);
	node = ms_env_list_find(*env_list, label);
	if (!node)
		return (NULL);
	env = node->content;
	if (!env)
		return (NULL);
	return (env->value);
}
