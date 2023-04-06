/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:42:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_list_update(t_list *node, char *value, int export)
{
	t_env	*env;
	char	*new_value;

	if (!node)
		return (FAILURE);
	env = (t_env *)(node->content);
	if (!env)
		return (FAILURE);
	if (value)
	{
		ft_free((void **)&(env->value));
		new_value = ft_strdup(value);
		if (!new_value)
			return (FAILURE);
		env->value = new_value;
	}
	if (export)
		env->export = 1;
	return (SUCCESS);
}
