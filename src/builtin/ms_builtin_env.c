/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:27:55 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 18:23:53 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_env(t_list **env_list)
{
	t_list	*node;
	t_env	*env;

	node = *env_list;
	while (node)
	{
		env = (t_env *)(node->content);
		if (env->value)
			printf("%s=%s\n", env->label, env->value);
		node = node->next;
	}
}
