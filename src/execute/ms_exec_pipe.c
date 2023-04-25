/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/25 21:01:41 by dapereir         ###   ########.fr       */
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
	t_cmd	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = data->cmds + cmd_id;
	if (ms_cmd_open_io_files(cmd) != SUCCESS)
		ms_exit(data, FAILURE);
	if (ms_fd_is_file(cmd->fd_in))
		ms_exec_dup2(data, cmd->fd_in, STDIN_FILENO);
	else if (cmd_id != 0)
		ms_exec_dup2(data, data->fd_pipe[2 * (cmd_id - 1)], STDIN_FILENO);
	if (ms_fd_is_file(cmd->fd_out))
		ms_exec_dup2(data, cmd->fd_out, STDOUT_FILENO);
	else if (cmd_id != data->cmd_size - 1)
		ms_exec_dup2(data, data->fd_pipe[2 * cmd_id + 1], STDOUT_FILENO);
	ms_exec_close_all_fd_pipes(data);
	ms_cmd_close_io_files(cmd);
	ms_exec_fork_cmd(data, cmd);
}

static int	ms_exec_wait_children(t_data *data, pid_t cpid[CMD_MAX], \
	int status[CMD_MAX])
{
	int		i;

	i = 0;
	while (i < data->cmd_size)
	{
		if (ms_is_cmd_to_fork(data, i))
			waitpid(cpid[i], status + i, 0);
		i++;
	}
	if (!ms_is_cmd_to_fork(data, data->cmd_size - 1))
		return (status[data->cmd_size - 1]);
	if (status[data->cmd_size - 1] == 2 || status[data->cmd_size - 1] == 3)
		return (status[data->cmd_size - 1] + 128);
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
		ms_cmd_declare_vars(data, data->cmds + i);
		if (!ms_is_cmd_to_fork(data, i))
			status[i] = ms_builtin_cmd(data, data->cmds[i].args);
		else
		{
			cpid[i] = fork();
			if (cpid[i] == -1)
				ms_error_exit(data, "fork failed", FAILURE);
			if (cpid[i] == 0)
				ms_exec_child_process(data, i);
		}
		i++;
	}
	ms_exec_close_all_fd_pipes(data);
	return (ms_exec_wait_children(data, cpid, status));
}
