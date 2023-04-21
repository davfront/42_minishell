/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_cmd_to_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/21 09:43:54 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_cmd_to_fork(t_data *data, int cmd_id)
{
	t_cmd	*cmd;

	if (!data || !data->cmds)
		return (0);
	cmd = data->cmds + cmd_id;
	if (!cmd || !cmd->args)
		return (0);
	if (ft_streq(cmd->args[0], "export") && cmd->args[1])
		return (0);
	if (ft_streq(cmd->args[0], "unset"))
		return (0);
	if (ft_streq(cmd->args[0], "cd") && cmd_id == data->cmd_size - 1)
		return (0);
	if (ft_streq(cmd->args[0], "exit") && cmd_id == data->cmd_size - 1)
		return (0);
	return (1);
}
