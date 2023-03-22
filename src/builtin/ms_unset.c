/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:09:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/24 13:21:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(t_list **env_list, char **args)
{
	t_list	*node;
	size_t	i;

	if (!env_list || !*env_list || !args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		node = ms_env_list_get_by_label(*env_list, args[i]);
		if (!node)
			return ;
		ms_env_list_delete(env_list, node);
		i++;
	}
}
