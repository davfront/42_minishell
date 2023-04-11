/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/11 17:30:59 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_parser(char *str, t_data *data)
{
	t_list	*list;
	char	*expanded_str;
	char	**cmds;

	list = data->env_list;
	expanded_str = ms_expand_var(str, list);
	cmds = ms_cmdsplit(expanded_str, " ");
	ft_free((void **)&expanded_str);
	if (!cmds)
		exit(EXIT_FAILURE);
	return (cmds);
}
