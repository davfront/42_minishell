/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens_remove_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:27:03 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/14 07:11:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_str_remove_first_char(char *s)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
}

static void	ms_str_remove_quotes(char *s)
{
	size_t	i;
	size_t	next_i;
	char	quote;
	char	*end;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		next_i = i + 1;
		if ((s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i];
			ms_str_remove_first_char(s + i);
			end = ft_strchr(s + i, quote);
			if (!end)
				return ;
			ms_str_remove_first_char(end);
			next_i = end - (s + i);
		}
		i = next_i;
	}
}

void	ms_tokens_remove_quotes(t_tok *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].type != END)
	{
		ms_str_remove_quotes(tokens[i].str);
		i++;
	}
}
