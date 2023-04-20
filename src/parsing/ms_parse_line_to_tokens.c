/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_line_to_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:53:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/20 22:42:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tok	*ms_convert_strs_to_tokens(char **strs)
{
	t_tok	*tokens;
	size_t	i;

	if (!strs)
		return (NULL);
	tokens = ft_calloc(ms_strs_len(strs) + 1, sizeof(t_tok));
	if (!tokens)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		tokens[i].str = strs[i];
		tokens[i].type = UNDEFINED;
		i++;
	}
	tokens[i].str = NULL;
	tokens[i].type = END;
	return (tokens);
}

static void	ms_type_tokens(t_tok *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].type != END)
	{
		if (ft_streq(tokens[i].str, "|"))
			tokens[i].type = PIPE;
		else if (ft_streq(tokens[i].str, "<"))
			tokens[i].type = REDIR_IN;
		else if (ft_streq(tokens[i].str, "<<"))
			tokens[i].type = HEREDOC;
		else if (ft_streq(tokens[i].str, ">"))
			tokens[i].type = REDIR_OUT;
		else if (ft_streq(tokens[i].str, ">>"))
			tokens[i].type = REDIR_OUT_APP;
		else
			tokens[i].type = WORD;
		i++;
	}
}

int	ms_parse_line_to_tokens(t_data *data)
{
	char	**strs;
	t_tok	*tokens;

	if (!data || !data->line)
		return (FAILURE);
	strs = ms_parser(data->line, data);
	if (!strs)
		return (FAILURE);
	tokens = ms_convert_strs_to_tokens(strs);
	ft_free((void **)&strs);
	if (!tokens)
		return (FAILURE);
	ms_type_tokens(tokens);
	data->tokens = tokens;
	ms_debug_tokens(data);
	if (!ms_check_tokens(data->tokens))
		return (MISUSE);
	ms_tokens_merge_io_args(data->tokens);
	ms_tokens_type_varset(data->tokens);
	ms_tokens_remove_quotes(data->tokens);
	ms_debug_tokens(data);
	return (SUCCESS);
}
