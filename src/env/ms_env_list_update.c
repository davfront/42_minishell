/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 16:53:19 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_list_update(t_list *node, char *value)
{
	t_env	*env;
	char	*new_value;

	if (!node)
		return (FAILURE);
	env = (t_env *)(node->content);
	if (!env)
		return (FAILURE);
	ft_free((void **)&(env->value));
	new_value = NULL;
	if (value)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (FAILURE);
	}
	env->value = new_value;
	return (SUCCESS);
}
