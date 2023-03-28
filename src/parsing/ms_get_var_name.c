/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_var_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:05:17 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 13:37:52 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_var_name(char *str, int j);

void    check_dollar(char **cmds, int i, int j)
{
    while (cmds[i])
    {
        while (cmds[i][j])
        {
            if (cmds[i][j] == '$' && cmds[i][j + 1] == '?')
                printf("WTF\n");
            else if (cmds[i][j] == '$')
                get_var_name(cmds[i], j + 1);
            j++;
        }
        j = 0;
        i++;
    }
}

static char *get_var_name(char *str, int j)
{
    int     start;
    int     end;
    char    *var;
    
    start = j;
    end = 0;
    while (ft_isalpha(str[j]) == 1)
    {
        j++;
        end++;
    }
    var = ft_substr(str, start, end);
    if (!var)
        return (NULL);
    //FONCTION AVEC ENV
    return (var);
}