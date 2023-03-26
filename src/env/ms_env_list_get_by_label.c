/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_get_by_label.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/25 12:19:09 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ms_env_list_get_by_label(t_list *env_list, char *label)
{
	t_list	*node;
	t_env	*env;

	if (!env_list || !label || !*label)
		return (NULL);
	node = env_list;
	while (node)
	{
		env = (t_env *)(node->content);
		if (env && env->label && ft_streq(env->label, label))
			return (node);
		node = node->next;
	}
	return (NULL);
}
