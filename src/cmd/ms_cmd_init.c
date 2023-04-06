/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:23:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/14 09:10:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_cmd_init_default(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->tokens = NULL;
	cmd->args = NULL;
	cmd->envp = NULL;
	cmd->exe_path = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
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

int	ms_cmd_init(t_cmd *cmd, t_tok *tokens)
{
	size_t	i;
	size_t	j;

	if (!cmd || !tokens)
		return (0);
	ms_cmd_init_default(cmd);
	cmd->tokens = tokens;
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
