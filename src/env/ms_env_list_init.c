/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:34:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 16:22:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_list_init(t_list **env_list, char **envp)
{
	t_env	*env;

	if (!envp)
		return (FAILURE);
	while (*envp)
	{
		env = ms_env_from_char(*envp);
		if (!env || ms_env_list_add(env_list, env) != SUCCESS)
		{
			ms_env_list_clear(env_list);
			return (FAILURE);
		}
		envp++;
	}
	return (SUCCESS);
}
