/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:21:12 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/28 14:26:49 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_cmd    *list_init(char **array);
// //static t_cmd    *new_node(char **array);

// void   create_list(char **array, int n_pipe)
// {
//     int         i;
//     t_cmd       *cmd;
    
//     i = 0;
//     printarr(array);
//     cmd = list_init(array);
//     if (!cmd)
//         exit(EXIT_FAILURE);
//     if (n_pipe > 1)
//     {
//         //NOUVELLE FONCTION
//         while (array[i] && array[i][0] != '|')
//             i++;
//         i++;
//         while (n_pipe > 0)
//         {
//             new_node(array, &i);
            
//         }
//     }
    

// }

// static t_cmd    *list_init(char **array)
// {
//     t_cmd   *lst;
//     int     end;

//     end = 0;
//     while (array[end] && array[end][0] != '|')
//         end++;
//     lst = malloc(sizeof(*lst));
//     if (!lst)
//         exit(EXIT_FAILURE);
//     lst->cmd = create_cmd_init(array, end);
//     if (!lst->cmd)
//         exit(EXIT_FAILURE);
//     lst->next = NULL;
//     return (lst);
// }

// static t_cmd    *new_node(char **array, int index)
// {
//     t_cmd   *new;

//     new = malloc(sizeof(*new));
//     if (!new)
//         exit(EXIT_FAILURE);
    
    
// }

// t_cmd   *new_cmd(char **array, int count, int *j)
// {
//     t_cmd   *new;

//     new = (t_cmd *)malloc(sizeof(t_cmd));
//     if (!new)
//         return (NULL);
//     new->cmd = create_cmd(array, count, j);
//     if (!new->cmd)
//         return (NULL);
//     printarr(new->cmd);
//     new->next = NULL;
//     return (new);
// }