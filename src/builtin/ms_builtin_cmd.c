/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:31:04 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 18:51:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_cmd(t_list **env_list, char **cmd_args)
{
	if (!cmd_args || !*cmd_args)
		return (FAILURE);
	if (ft_streq(cmd_args[0], "pwd"))
		ms_builtin_pwd();
	else if (ft_streq(cmd_args[0], "echo"))
		ms_builtin_echo(cmd_args + 1);
	else if (ft_streq(cmd_args[0], "env"))
		ms_builtin_env(env_list);
	else if (ft_streq(cmd_args[0], "export"))
		return (ms_builtin_export(env_list, cmd_args + 1));
	else if (ft_streq(cmd_args[0], "unset"))
		ms_unset(env_list, cmd_args + 1);
	else if (ft_streq(cmd_args[0], "cd"))
		return (ms_builtin_cd(env_list, cmd_args + 1));
	else if (ft_streq(cmd_args[0], "exit"))
		ms_builtin_exit(env_list, cmd_args + 1);
	else if (!ms_is_builtin_cmd(cmd_args[0]))
		return (FAILURE);
	return (SUCCESS);
}
