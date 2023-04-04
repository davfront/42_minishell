/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/04 15:33:01 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printarr(char **cmd)
{
	for (int i = 0; cmd[i]; i++)
	{
		if (cmd[i])
			printf("[%d]=%s\n", i, cmd[i]);
	}
	printf("\n");
}

char	**ms_parser(char *str, t_data *data)
{
	char	**cmds;
	t_list	*list;

	list = data->env_list;
	cmds = ms_cmdsplit(ms_expand_var(str, list), " ");
	if (!cmds)
		exit(EXIT_FAILURE);
	printarr(cmds);
	return (cmds);
}
