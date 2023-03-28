/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:05:01 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 13:38:57 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_rows(char *str, char *set);
static char **ft_str(char **arr, char *str, char *set);

char    **ft_cmdtrim(char *str, char *set)
{
    char    **array;
    int     count;

    if (!str)
        return (NULL);
    count = count_rows(str, set);
    array = malloc((count + 1) * sizeof(char *));
    if (!array)
        return (NULL);
    array = ft_str(array, str, set);
    array[count] = '\0';
    return (array);
}

static char **ft_str(char **arr, char *str, char *set)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int quotes = 0;
    int len = ft_strlen(str);

    while (str[i] != '\0')
    {
        while (ft_strchr(set, str[i]) && str[i] != '\0')
            i++;
        j = i;
        while (str[i] != '\0')
        {
            if ((str[i] == '\"' || str[i] == '\'') && !quotes)
                quotes = str[i];
            else if (str[i] == quotes)
                quotes = 0;
            else if (ft_strchr(set, str[i]) && !quotes)
                break;
            i++;
        }
        if (j >= len)
            arr[k++] = "\0";
        else
            arr[k++] = ft_substr(str, j, i - j);
    }
    return (arr);
}

static int count_rows(char *str, char *set)
{
    int count = 0;
    int quotes = 0;

    while (*str)
    {
        if (!ft_strchr(set, *str))
        {
            count++;
            while ((!ft_strchr(set, *str) || quotes) && *str)
            {
                if (!quotes && (*str == '\"' || *str == '\''))
                    quotes = *str;
                else if (quotes == *str)
                    quotes = 0;
                str++;
            }
        }
        else
            str++;
    }
    return (count);
}

