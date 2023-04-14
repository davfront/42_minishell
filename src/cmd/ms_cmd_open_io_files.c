/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_open_io_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:51:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/14 08:57:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmd_open_file_in(t_cmd *cmd, char *path)
{
	if (ms_fd_is_file(cmd->fd_in))
		close(cmd->fd_in);
	cmd->fd_in = open(path, O_RDONLY);
	if (cmd->fd_in == -1)
		return (ms_perror(path), FAILURE);
	return (SUCCESS);
}

static int	ms_cmd_open_file_out(t_cmd *cmd, char *path, int append)
{
	if (ms_fd_is_file(cmd->fd_out))
		close(cmd->fd_out);
	if (append)
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return (ms_perror(path), FAILURE);
	return (SUCCESS);
}

int	ms_cmd_open_io_files(t_cmd *cmd)
{
	size_t	i;
	int		ret;

	if (!cmd || !cmd->tokens)
		return (FAILURE);
	ret = SUCCESS;
	i = 0;
	while (!ms_token_is_cmd_sep(cmd->tokens[i]))
	{
		if (cmd->tokens[i].type == REDIR_IN)
			ret = ms_cmd_open_file_in(cmd, cmd->tokens[i].str);
		else if (cmd->tokens[i].type == REDIR_OUT)
			ret = ms_cmd_open_file_out(cmd, cmd->tokens[i].str, 0);
		else if (cmd->tokens[i].type == REDIR_OUT_APP)
			ret = ms_cmd_open_file_out(cmd, cmd->tokens[i].str, 1);
		if (ret != SUCCESS)
			return (ret);
		i++;
	}
	return (SUCCESS);
}
