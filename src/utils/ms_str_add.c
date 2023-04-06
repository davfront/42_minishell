/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:58:25 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/17 05:52:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_str_add(char **s, char *s2)
{
	char	*new_s;

	if (!s)
		return ;
	new_s = ft_strjoin(*s, s2);
	ft_free((void **)s);
	*s = new_s;
}
