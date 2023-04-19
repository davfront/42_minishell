/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:36:05 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 14:50:01 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_print_token_error(char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int	ms_check_tokens(char **tokens)
{
	size_t	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (i == 0 && ft_streq(tokens[i], "|"))
			return (ms_print_token_error("|"), 0);
		if (ms_token_is_sep(tokens[i]) && ms_token_is_sep(tokens[i + 1]))
			return (ms_print_token_error(tokens[i + 1]), 0);
		if (ms_token_is_io_sep(tokens[i]) && !tokens[i + 1])
			return (ms_print_token_error("newline"), 0);
		i++;
	}
	return (1);
}
