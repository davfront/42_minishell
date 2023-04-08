/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:28:33 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 16:24:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_exec_init_pipes(t_data *data)
{
	int		i;

	if (!data || !data->cmd_size || !data->cmds)
		return (FAILURE);
	if (data->cmd_size == 1)
		return (SUCCESS);
	data->fd_pipe = ft_calloc(2 * (data->cmd_size - 1), sizeof(int));
	if (!data->fd_pipe)
		return (FAILURE);
	i = 0;
	while (i < 2 * (data->cmd_size - 1))
	{
		data->fd_pipe[i] = -1;
		i++;
	}
	return (SUCCESS);
}

int	ms_exec_cmds(t_data *data)
{
	if (!data || !data->cmd_size || !data->cmds)
		return (FAILURE);
	if (ms_exec_init_pipes(data) != SUCCESS)
		return (FAILURE);
	return (ms_exec_pipe(data));
}
