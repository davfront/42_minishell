/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_tokens_to_cmds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:23:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/13 21:07:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_get_cmd_size(t_data *data)
{
	t_tok	*tokens;

	if (!data || !data->tokens || data->tokens[0].type == END)
	{
		data->cmd_size = 0;
		return (0);
	}
	data->cmd_size = 1;
	tokens = data->tokens;
	while (tokens->type != END)
	{
		if (tokens->type == PIPE)
			data->cmd_size++;
		tokens++;
	}
	return (data->cmd_size);
}

static int	ms_get_cmd_args_size(t_tok *tokens)
{
	size_t	i;
	size_t	len;

	if (!tokens)
		return (0);
	i = 0;
	len = 0;
	while (!ms_token_is_cmd_sep(tokens[i]))
	{
		if (ms_token_is_io_sep(tokens[i]) \
			&& !ms_token_is_cmd_sep(tokens[i + 1]))
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

static int	ms_init_cmd(t_cmd *cmd, t_tok *tokens)
{
	size_t	i;
	size_t	j;

	if (!cmd || !tokens)
		return (0);
	cmd->envp = NULL;
	cmd->exe_path = NULL;
	cmd->args = ft_calloc(ms_get_cmd_args_size(tokens) + 1, sizeof(char *));
	if (!cmd->args)
		return (0);
	i = 0;
	j = 0;
	while (!ms_token_is_cmd_sep(tokens[i]))
	{
		if (tokens[i].type == WORD)
		{
			cmd->args[j] = tokens[i].str;
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
	if (!ms_init_cmd(data->cmds, data->tokens))
		return (ms_reset_cmds(data), FAILURE);
	j = 1;
	i = 0;
	while (data->tokens[i].type != END && j < data->cmd_size)
	{
		if (data->tokens[i].type == PIPE)
		{
			if (!ms_init_cmd(data->cmds + j, data->tokens + i + 1))
				return (ms_reset_cmds(data), FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ms_parse_tokens_to_cmds(t_data *data)
{
	if (!data || !data->tokens)
		return (FAILURE);
	if (ms_get_cmd_size(data) < 1)
		return (FAILURE);
	if (ms_get_cmds(data) != SUCCESS)
		return (FAILURE);
	ms_debug_cmds(data);
	return (SUCCESS);
}
