/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:09:23 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/03 17:14:50 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ms_tilde(char *str, t_list *env)
{
    int     i;
    char    *home;

    i = 0;
    while (str[i])
    {
        if (str[i] == '~')
        {
            home = ms_get_home(env);
            if (!home)
                return (NULL);
        }
    }
}

static char *ms_get_home(t_list *env)
{
    t_list  *head;
    t_env   *tmp;
    char    *home;

    head = env;
    tmp = (t_env *)head->content;
    while (head->next != NULL)
    {
        if (ft_streq("HOME", tmp->label))
        {
            home = ft_strdup(tmp->value);
            if (!home)
                exit(EXIT_FAILURE);
            return (home);
        }
        head = head->next;
    }
    return (NULL);
}