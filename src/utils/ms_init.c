/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/17 04:28:10 by dapereir         ###   ########.fr       */
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
	data->fd_pipe = NULL;
	data->heredoc_enabled = 0;
	data->heredoc_delimiter = NULL;
	data->heredoc_fd = -1;
}

int	ms_init(t_data *data, int argc, char **argv, char **envp)
{
	if (!data)
		return (FAILURE);
	ms_init_default(data);
	if (ms_env_list_init(&(data->env_list), envp) != SUCCESS)
		return (FAILURE);
	return (ms_env_list_set(&(data->env_list), "_", argv[argc - 1], 1));
}
