/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens_merge_io_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:27:03 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 21:00:36 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_remove_token(t_tok *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].type != END)
	{
		tokens[i].type = tokens[i + 1].type;
		tokens[i].str = tokens[i + 1].str;
		i++;
	}
}

void	ms_tokens_merge_io_args(t_tok *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].type != END)
	{
		if (ms_token_is_io_sep(tokens[i]) && !ms_token_is_sep(tokens[i + 1]))
		{
			ft_free((void **)&(tokens[i].str));
			tokens[i].str = tokens[i + 1].str;
			tokens[i + 1].str = NULL;
			ms_remove_token(tokens + i + 1);
		}
		i++;
	}
}
