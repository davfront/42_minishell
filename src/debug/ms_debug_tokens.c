/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:35:33 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 19:28:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_print_type(t_type type)
{
	if (type == UNDEFINED)
		ft_putstr("UNDEFINED");
	else if (type == PIPE)
		ft_putstr("PIPE");
	else if (type == HEREDOC)
		ft_putstr("HEREDOC");
	else if (type == REDIR_IN)
		ft_putstr("REDIR_IN");
	else if (type == REDIR_OUT)
		ft_putstr("REDIR_OUT");
	else if (type == REDIR_OUT_APP)
		ft_putstr("REDIR_OUT_APP");
	else if (type == WORD)
		ft_putstr("WORD");
	else if (type == VARSET)
		ft_putstr("VARSET");
	else
		ft_putnbr(type);
}

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
	while (data->tokens[i].type != END)
	{
		ft_printf(" [");
		ms_print_type(data->tokens[i].type);
		ft_printf(":%s]", data->tokens[i].str);
		i++;
	}
	ft_printf("\n\033[0m");
}
