/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:27:55 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 22:31:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_env(t_data *data)
{
	t_list	*node;
	t_env	*env;

	node = data->env_list;
	while (node)
	{
		env = (t_env *)(node->content);
		if (env->value && env->export)
			ft_printf("%s=%s\n", env->label, env->value);
		node = node->next;
	}
}
