/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:46:32 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 14:40:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_cmds(t_data *data)
{
	int		i;
	char	**cmd_args;
	t_cmd	*cmds;

	if (!DEBUG || !data)
		return ;
	cmds = data->cmds;
	ft_printf("\033[2m");
	i = 0;
	while (i < data->cmd_size)
	{
		ft_printf("cmds[%i]: ", i);
		cmd_args = cmds[i].args;
		while (*cmd_args)
		{
			ft_printf("[%s] ", *cmd_args);
			cmd_args++;
		}
		i++;
		ft_printf("\n");
	}
	ft_printf("\033[0m");
}
