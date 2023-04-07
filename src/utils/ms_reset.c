/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 15:02:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_reset_cmds(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < data->cmd_size)
	{
		if (data->cmds[i].args)
			ft_free((void **)&(data->cmds[i].args));
		i++;
	}
	ft_free((void **)&(data->cmds));
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
