/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 14:34:19 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init_default(t_data *data)
{
	if (!data)
		return ;
	data->env_list = NULL;
	data->line = NULL;
	data->tokens = NULL;
	data->cmd_size = 0;
	data->cmds = NULL;
}

void	ms_init(t_data *data, char **envp)
{
	if (!data)
		return ;
	ms_init_default(data);
	ms_env_list_init(&(data->env_list), envp);
}
