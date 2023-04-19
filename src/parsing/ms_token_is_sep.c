/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_is_sep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:42:01 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 15:55:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_token_is_cmd_sep(t_tok token)
{
	if (token.type == PIPE)
		return (1);
	if (token.type == END)
		return (1);
	return (0);
}

int	ms_token_is_io_sep(t_tok token)
{
	if (token.type == REDIR_IN)
		return (1);
	if (token.type == HEREDOC)
		return (1);
	if (token.type == REDIR_OUT)
		return (1);
	if (token.type == REDIR_OUT_APP)
		return (1);
	return (0);
}

int	ms_token_is_sep(t_tok token)
{
	if (ms_token_is_cmd_sep(token))
		return (1);
	if (ms_token_is_io_sep(token))
		return (1);
	return (0);
}
