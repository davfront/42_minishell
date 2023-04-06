/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_from_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:07:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_from_char(char *s, int export)
{
	t_env	*env;
	char	*substr;

	if (!s)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->label = NULL;
	env->value = NULL;
	env->export = export;
	substr = ft_strchr(s, '=');
	if (substr)
	{
		env->label = ft_strndup(s, substr - s);
		env->value = ft_strdup(substr + 1);
	}
	else
		env->label = ft_strdup(s);
	if (!env->label || (substr && !env->value))
	{
		ms_env_delete(env);
		return (NULL);
	}
	return (env);
}
