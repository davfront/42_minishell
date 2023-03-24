/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_from_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 10:23:06 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_from_char(char *s)
{
	t_env	*env;
	char	*substr;

	if (!s)
		return (NULL);
	env = malloc(sizeof(t_env));
	env->label = NULL;
	env->value = NULL;
	substr = ft_strchr(s, '=');
	if (substr)
	{
		env->label = ft_strndup(s, substr - s);
		// todo: protect malloc
		env->value = ft_strdup(substr + 1);
		// todo: protect malloc
	}
	else
		env->label = ft_strdup(s);
		// todo: protect malloc
	return (env);
}
