/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:35:33 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 14:40:51 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_tokens(t_data *data)
{
	size_t	i;

	if (!DEBUG)
		return ;
	ft_printf("\033[2mtokens:");
	if (!data || !data->tokens)
	{
		ft_printf("NULL\n\033[0m");
		return ;
	}
	i = 0;
	while (data->tokens[i])
	{
		ft_printf(" [%s]", data->tokens[i]);
		i++;
	}
	ft_printf("\n\033[0m");
}
