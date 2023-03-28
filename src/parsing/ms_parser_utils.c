/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:05:12 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 10:05:57 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    del_char(char *str, char c)
{
    char    *copy;
    char    *tmp;

    copy = str;
    while (*copy)
    {
        if (*copy == c)
        {
            tmp = copy;
            while (*tmp)
            {
                *tmp = *(tmp + 1);
                tmp++;
            }
        }
        else
            copy++;
    }
}

int     is_option(char *str)
{
    char    *tmp;
    int     i;

    tmp = ft_strdup(str);
    i = 0;
    del_char(tmp, '\'');
    del_char(tmp, '\"');
    while (tmp[i])
    {
        if (check_char_option(tmp[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int	check_char_option(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
    else if (c == '-')
        return (1);
    else if (c == '=')
        return (1);
	else
		return (0);
}