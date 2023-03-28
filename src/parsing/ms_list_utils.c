/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:12:29 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 13:57:14 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_pipe(char *str)
{
    int     count;
    int     i;

    count = 1;
    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    return (count);
}

char    **create_cmd_init(char **array, int count)
{
    int     i;
    char    **cmd;
    
    i = 0;
    cmd = malloc((count + 1) * sizeof(char *));
    if (!cmd)
        return (NULL);
    while (i < count)
    {
        cmd[i] = ft_strdup(array[i]);
        if (!cmd[i])
            return (NULL);
        i++;
    }
    cmd[count] = '\0';
    return (cmd);
}

int     count_items_cmd(char **array, int *i)
{
    int     count;

    count = 0;
    while (array[*i])
    {
        if (array[*i][0] == '|')
            return (count);
        count++;
        (*i)++;
    }
    return (count);
}

int     ft_index(char **array)
{
    int     i;

    i = 0;
    if (!array)
        return (-1);
    while (array[i] && array[i][0] != '|')
        i++;
    return (i);
}


