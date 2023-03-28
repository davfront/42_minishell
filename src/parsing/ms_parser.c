/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 14:36:02 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printarr(char **arr)
{
    printf("---------------------------------\n");
    for(int i = 0; arr[i]; i++)
        printf("%s\n", arr[i]);
    printf("---------------------------------\n\n");
}


int    parser(char *str)
{
    char    **cmds;
    //int     n_pipes;

    cmds = ft_cmdtrim(str, " ");
    if (!cmds)
        return (-1);
    ms_clean_commands(cmds);
    check_dollar(cmds, 0, 0);
    printarr(cmds);
    //n_pipes = count_pipe(str);
    //create_list(cmds, n_pipes);
    //n = count_items_cmd(cmds);
    //create_cmd(cmds, n);
    //printarr(cmds);
    return (0);
}
