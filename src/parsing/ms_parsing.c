/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/24 14:44:17 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printarr(char **arr)
{
    for(int i = 0; arr[i]; i++)
        printf("%s\n", arr[i]);
    printf("\n");
}


void    parser(char *str)
{
    int     i;
    char    **cmd;

    i = 0;
    cmd = ft_split(str, '|');
    if (!cmd)
        exit(EXIT_FAILURE);

}
