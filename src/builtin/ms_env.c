/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:27:55 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 10:58:47 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_list **env_list)
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
