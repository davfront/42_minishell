/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens_type_varset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:27:03 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 21:01:47 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_token_is_varset(t_tok token)
{
	char	*s;
	size_t	i;

	s = token.str;
	if (!s || !*s)
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (i == 0)
		return (0);
	return (s[i] == '=');
}

void	ms_tokens_type_varset(t_tok *tokens)
{
	size_t	i;
	int		word_found;

	if (!tokens)
		return ;
	word_found = 0;
	i = 0;
	while (tokens[i].type != END)
	{
		if (i == 0 || tokens[i - 1].type == PIPE)
			word_found = 0;
		if (tokens[i].type == WORD)
		{
			if (!word_found && ms_token_is_varset(tokens[i]))
				tokens[i].type = VARSET;
			else
				word_found = 1;
		}
		i++;
	}
}
