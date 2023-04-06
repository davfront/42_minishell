/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osterger <osterger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:43:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/06 02:43:26 by osterger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_parser(char *str, t_data *data)
{
	char	*expanded_str;
	char	*expanded_str2;
	char	**tokens;

	expanded_str = ms_expand_var(str, data);
	if (!expanded_str)
		return (NULL);
	expanded_str2 = ms_tilde(expanded_str, data);
	tokens = ms_cmdsplit(expanded_str2, " \t");
	ft_free((void **)&expanded_str);
	ft_free((void **)&expanded_str2);
	return (tokens);
}
