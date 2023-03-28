/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:05:36 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 14:36:02 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void clean_quotes(char *str);

void    ms_clean_commands(char **cmds)
{
    int     i;
    int     status;

    i = 1;
    status = 0;
    clean_quotes(cmds[0]);
    while (cmds[i])
    {
        if (cmds[i][0] == '|')
            status = 1;
        if (status == 1)
        {
            clean_quotes(cmds[i + 1]);
            status = 0;
        }
        if (is_option(cmds[i]) == 1)
            clean_quotes(cmds[i]);
        i++;
    }
}

static void clean_quotes(char *str)
{
    del_char(str, '\'');
    del_char(str, '\"');
}