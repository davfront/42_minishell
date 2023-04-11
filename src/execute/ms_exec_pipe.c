/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/11 11:05:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exec_set_all_fd_pipes(t_data *data)
{
	int	i;
	int	*fd_pipe;

	i = 0;
	while (i < data->cmd_size - 1)
	{
		fd_pipe = data->fd_pipe + 2 * i;
		if (pipe(fd_pipe) == -1)
			ms_error_exit(data, "pipe failed", FAILURE);
		i++;
	}
}

static void	ms_exec_close_all_fd_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2 * (data->cmd_size - 1))
	{
		close(data->fd_pipe[i]);
		i++;
	}
}

static void	ms_exec_child_process(t_data *data, int cmd_id)
{
	if (cmd_id != 0)
		ms_exec_dup2(data, data->fd_pipe[2 * (cmd_id - 1)], STDIN_FILENO);
	if (cmd_id != data->cmd_size - 1)
		ms_exec_dup2(data, data->fd_pipe[2 * cmd_id + 1], STDOUT_FILENO);
	ms_exec_close_all_fd_pipes(data);
	ms_exec_fork_cmd(data, data->cmds + cmd_id);
}

static int	ms_exec_wait_children(t_data *data, pid_t cpid[CMD_MAX], \
	int status[CMD_MAX])
{
	int		i;

	i = 0;
	while (i < data->cmd_size)
	{
		waitpid(cpid[i], status + i, 0);
		i++;
	}
	if (WIFEXITED(status[data->cmd_size - 1]))
		return (WEXITSTATUS(status[data->cmd_size - 1]));
	return (SUCCESS);
}

int	ms_exec_pipe(t_data *data)
{
	pid_t	cpid[CMD_MAX];
	int		i;
	int		status[CMD_MAX];

	ms_exec_set_all_fd_pipes(data);
	i = 0;
	while (i < data->cmd_size)
	{
		if (data->cmds[i].args && data->cmds[i].args[0])
		{
			if (ms_is_builtin_cmd_no_fork(data->cmds[i].args[0]))
				status[i] = ms_builtin_cmd(data, data->cmds[i].args);
			else
			{
				cpid[i] = fork();
				if (cpid[i] == -1)
					ms_error_exit(data, "fork failed", FAILURE);
				if (cpid[i] == 0)
					ms_exec_child_process(data, i);
			}
		}
		i++;
	}
	ms_exec_close_all_fd_pipes(data);
	return (ms_exec_wait_children(data, cpid, status));
}
