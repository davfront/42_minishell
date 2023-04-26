/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_create_tmp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:21:12 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/26 01:21:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_heredoc_print_eof_warning(t_data *data)
{
	if (!data)
		return ;
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited at line ", STDERR_FILENO);
	ft_putnbr_fd(data->line_no, STDERR_FILENO);
	ft_putstr_fd(" by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(data->heredoc_delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static int	ms_heredoc_edit_tmp(t_data *data)
{
	char	*line;
	int		line_len;

	if (!data || data->heredoc_fd == -1)
		return (FAILURE);
	line = NULL;
	line_len = 0;
	while (!line || !ft_streq(line, data->heredoc_delimiter))
	{
		if (line && data->heredoc_enabled == 1)
		{
			ft_putstr_fd(line, data->heredoc_fd);
			ft_free((void **)&line);
			ft_putstr_fd("\n", data->heredoc_fd);
		}
		line = readline(PS2);
		if (!line)
		{
			ms_heredoc_print_eof_warning(data);
			break ;
		}
		line_len++;
	}
	data->line_no += line_len;
	return (ft_free((void **)&line), SUCCESS);
}

static int	ms_heredoc_parse(t_data *data)
{
	size_t	i;

	if (!data || !data->tokens)
		return (FAILURE);
	i = 0;
	while (data->tokens[i].type != END)
	{
		if (data->tokens[i].type == HEREDOC)
		{
			data->heredoc_enabled++;
			data->heredoc_delimiter = data->tokens[i].str;
		}
		i++;
	}
	return (SUCCESS);
}

int	ms_heredoc_create_tmp(t_data *data)
{
	if (!data)
		return (FAILURE);
	if (ms_heredoc_parse(data) != SUCCESS)
		return (FAILURE);
	if (!data->heredoc_enabled)
		return (SUCCESS);
	data->heredoc_fd = open(HEREDOC_TMP, O_CREAT | O_RDWR | O_TRUNC);
	if (data->heredoc_fd == -1)
		return (FAILURE);
	if (ms_heredoc_edit_tmp(data) != SUCCESS)
		return (FAILURE);
	close(data->heredoc_fd);
	return (SUCCESS);
}
