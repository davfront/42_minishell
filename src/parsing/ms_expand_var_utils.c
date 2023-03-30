/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:36:26 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/30 13:38:39 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ms_content_len(int index, char *str)
{
	int		count;

	count = 0;
	while (str[index])
	{
		index++;
		count++;
	}
	return (count);
}

int     ms_count_var(char *str)
{
    int     i;
    int     size;

    i = 0;
    size = 0;
    while (str[i])
    {
        if ((str[i] == '$' && !ms_is_quote(str[i + 1])) || \
        (str[i] == '$' && str[i + 1] == '?'))
            size++;
        i++;
    }
    return (size);
}