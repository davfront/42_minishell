/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:23:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 15:23:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_get_cmd_size(t_data *data)
{
	char	**tokens;

	if (!data || !data->tokens)
		return (0);
	if (!data || !data->tokens || !data->tokens[0])
	{
		data->cmd_size = 0;
		return (0);
	}
	data->cmd_size = 1;
	tokens = data->tokens;
	while (*tokens)
	{
		if (ft_streq(*tokens, "|"))
			data->cmd_size++;
		tokens++;
	}
	return (data->cmd_size);
}

static int	ms_get_cmd_args_size(char **tokens)
{
	size_t	i;
	size_t	len;

	if (!tokens)
		return (0);
	i = 0;
	len = 0;
	while (tokens[i] && !ft_streq(tokens[i], "|"))
	{
		if (ms_token_is_io_sep(tokens[i]) && tokens[i + 1])
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

static int	ms_get_cmd_args(t_cmd *cmd, char **tokens)
{
	size_t	i;
	size_t	j;

	if (!cmd || !tokens)
		return (0);
	cmd->args = ft_calloc(ms_get_cmd_args_size(tokens) + 1, sizeof(char *));
	if (!cmd->args)
		return (0);
	i = 0;
	j = 0;
	while (tokens[i] && !ft_streq(tokens[i], "|"))
	{
		if (ms_token_is_io_sep(tokens[i]) && tokens[i + 1])
			i++;
		else
		{
			cmd->args[j] = tokens[i];
			j++;
		}
		i++;
	}
	cmd->args[j] = NULL;
	return (1);
}

static int	ms_get_cmds(t_data *data)
{
	int		i;
	int		j;

	if (!data || !data->cmd_size || !data->tokens)
		return (FAILURE);
	data->cmds = ft_calloc(data->cmd_size, sizeof(t_cmd));
	if (!data->cmds)
		return (FAILURE);
	if (!ms_get_cmd_args(data->cmds, data->tokens))
		return (ms_reset_cmds(data), FAILURE);
	j = 1;
	i = 0;
	while (data->tokens[i] && j < data->cmd_size)
	{
		if (ft_streq(data->tokens[i], "|"))
		{
			if (!ms_get_cmd_args(data->cmds + j, data->tokens + i + 1))
				return (ms_reset_cmds(data), FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ms_parse_tokens(t_data *data)
{
	if (!data || !data->tokens)
		return (FAILURE);
	if (!ms_check_tokens(data->tokens))
		return (MISUSE);
	if (!ms_get_cmd_size(data))
		return (FAILURE);
	return (ms_get_cmds(data));
}
