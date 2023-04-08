/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 15:37:37 by dapereir         ###   ########.fr       */
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
			if (data->cmds[i].args)
				ft_free((void **)&(data->cmds[i].args));
			if (data->cmds[i].envp)
				ft_free_split(data->cmds[i].envp);
			i++;
		}
		ft_free((void **)&(data->cmds));
	}
	ms_reset_pipes(data);
	data->cmd_size = 0;
}

void	ms_reset_prompt(t_data *data)
{
	if (!data)
		return ;
	ft_free((void **)&(data->line));
	ft_free_split(data->tokens);
	ms_reset_cmds(data);
}

void	ms_reset(t_data *data)
{
	if (!data)
		return ;
	ms_env_list_clear(&(data->env_list));
	rl_clear_history();
	ms_reset_prompt(data);
}
