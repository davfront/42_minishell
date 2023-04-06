/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reset_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/17 05:14:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_reset_pipes(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->fd_pipe)
	{
		i = 0;
		while (i < 2 * (data->cmd_size - 1))
		{
			if (data->fd_pipe[i] != -1)
				close(data->fd_pipe[i]);
			i++;
		}
		ft_free((void **)&data->fd_pipe);
	}
}

static void	ms_reset_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->tokens = NULL;
	if (cmd->args)
		ft_free((void **)&(cmd->args));
	if (cmd->envp)
		ft_free_split(cmd->envp);
	ft_free((void **)&(cmd->exe_path));
	ms_cmd_close_io_files(cmd);
}

void	ms_reset_cmds(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->cmds)
	{
		i = 0;
		while (i < data->cmd_size)
		{
			ms_reset_cmd(data->cmds + i);
			i++;
		}
		ft_free((void **)&(data->cmds));
	}
	ms_reset_pipes(data);
	data->cmd_size = 0;
}
