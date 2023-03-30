/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/30 17:59:08 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void printarr(char **cmd)
{
    for (int i = 0; cmd[i]; i++)
    {
        if (cmd[i])
            printf("[%d]=%s\n", i, cmd[i]);
    }
    printf("\n");
}

char	**ms_parser(char *str, char **env)
{
	char	**cmds;

	ms_expand_var(str, env);
	cmds = ms_cmdsplit(str, " ");
	if (!cmds)
		exit(EXIT_FAILURE);
	printarr(cmds);
	//ft_free_split(cmds);
	return (cmds);
}
