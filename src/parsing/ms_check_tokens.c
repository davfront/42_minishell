/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:36:05 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 19:28:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_print_token_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int	ms_check_tokens(t_tok *tokens)
{
	size_t	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i].type != END)
	{
		if (i == 0 && tokens[i].type == PIPE)
			return (ms_print_token_error("|"), 0);
		if ((ms_token_is_cmd_sep(tokens[i]) \
				&& ms_token_is_cmd_sep(tokens[i + 1])) \
			|| (ms_token_is_io_sep(tokens[i]) \
				&& ms_token_is_sep(tokens[i + 1])))
		{
			if (tokens[i + 1].type == END)
				return (ms_print_token_error("newline"), 0);
			else
				return (ms_print_token_error(tokens[i + 1].str), 0);
		}
		i++;
	}
	return (1);
}
