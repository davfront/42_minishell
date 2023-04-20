/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 16:03:51 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exec_script_cmd(t_data *data, t_cmd *cmd)
{
	char	*exe_path;

	if (!data || !cmd)
		ms_exit(data, FAILURE);
	exe_path = cmd->exe_path;
	if (!exe_path)
		exe_path = cmd->args[0];
	if (access(exe_path, F_OK) == -1)
		ms_perror_exit(data, cmd->args[0], NOT_FOUND);
	if (access(exe_path, X_OK) == -1)
		ms_perror_exit(data, cmd->args[0], CANT_EXEC);
	if (execve(exe_path, cmd->args, cmd->envp) == -1)
		ms_perror_exit(data, cmd->args[0], FAILURE);
	ms_exit(data, SUCCESS);
}

void	ms_exec_fork_cmd(t_data *data, t_cmd *cmd)
{
	if (!cmd)
		ms_exit(data, FAILURE);
	if (ft_streq(cmd->args[0], ":"))
		ms_exit(data, SUCCESS);
	if (ms_is_builtin_cmd(cmd->args[0]))
		ms_exit(data, ms_builtin_cmd(data, cmd->args));
	if (ms_is_directory(cmd->args[0]))
	{
		ms_error2(cmd->args[0], "Is a directory");
		ms_exit(data, CANT_EXEC);
	}
	cmd->envp = ms_env_list_export(data->env_list);
	if (!cmd->envp)
		ms_exit(data, FAILURE);
	if (ms_is_script_cmd(cmd->args[0]))
		ms_exec_script_cmd(data, cmd);
	cmd->exe_path = ms_cmd_get_bin_path(data, cmd->args[0]);
	if (cmd->exe_path)
		ms_exec_script_cmd(data, cmd);
	ms_error2(cmd->args[0], "command not found");
	ms_exit(data, NOT_FOUND);
}
