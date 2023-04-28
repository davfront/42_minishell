/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:31:04 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/28 10:48:16 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_cmd(t_data *data, char **cmd_args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!data || !cmd_args || !*cmd_args)
		return (FAILURE);
	if (ft_streq(cmd_args[0], "pwd"))
		ms_builtin_pwd();
	else if (ft_streq(cmd_args[0], "echo"))
		ms_builtin_echo(cmd_args + 1);
	else if (ft_streq(cmd_args[0], "env"))
		ms_builtin_env(data);
	else if (ft_streq(cmd_args[0], "export"))
		return (ms_builtin_export(data, cmd_args + 1));
	else if (ft_streq(cmd_args[0], "unset"))
		ms_unset(data, cmd_args + 1);
	else if (ft_streq(cmd_args[0], "cd"))
		return (ms_builtin_cd(data, cmd_args + 1));
	else if (ft_streq(cmd_args[0], "exit"))
	{
		if (ms_builtin_exit(data, cmd_args + 1) != SUCCESS)
			return (FAILURE);
	}
	else if (!ms_is_builtin_cmd(cmd_args[0]))
		return (FAILURE);
	return (SUCCESS);
}
