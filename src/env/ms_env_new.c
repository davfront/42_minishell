/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 10:48:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_new(char *label, char *value)
{
	t_env	*env;

	if (!ms_env_is_valid_identifier(label))
		return (NULL);
	env = malloc(sizeof(t_env));
	// todo: protect malloc
	env->label = ft_strdup(label);
	// todo: protect malloc
	if (value)
	{
		env->value = ft_strdup(value);
		// todo: protect malloc
	}
	return (env);
}
