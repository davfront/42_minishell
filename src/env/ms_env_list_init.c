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

void	ms_env_list_init(t_list **env_list, char **envp)
{
	char	*substr;
	char	*label;
	char	*value;

	if (!envp)
		return ;
	while (*envp)
	{
		substr = ft_strchr(*envp, '=');
		if (substr && substr > *envp)
		{
			value = substr + 1;
			label = ft_strndup(*envp, substr - *envp);
			// todo: protect malloc
			ms_env_list_add(env_list, label, value);
			ft_free((void **)(&label));
		}
		envp++;
	}
}
