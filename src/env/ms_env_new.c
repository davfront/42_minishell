/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:22:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_new(char *label, char *value, int export)
{
	t_env	*env;

	if (!ms_env_is_valid_identifier(label))
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->label = ft_strdup(label);
	env->value = NULL;
	env->export = export;
	if (!env->label)
	{
		ms_env_delete(env);
		return (NULL);
	}
	if (value)
	{
		env->value = ft_strdup(value);
		if (!env->value)
		{
			ms_env_delete(env);
			return (NULL);
		}
	}
	return (env);
}
