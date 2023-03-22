/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 19:48:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_list_add(t_list **env_list, char *label, char *value)
{
	t_env	*env;
	void	*new_content;

	if (!env_list || !label || !value)
		return ;
	env = malloc(sizeof(t_env));
	// todo: protect malloc
	env->label = ft_strdup(label);
	// todo: protect malloc
	env->value = ft_strdup(value);
	// todo: protect malloc
	new_content = ft_lstnew(env);
	// todo: protect malloc
	ft_lstadd_back(env_list, new_content);
}
