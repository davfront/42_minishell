/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reset_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:44 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/20 12:31:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_reset_tokens(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->tokens)
	{
		i = 0;
		while (data->tokens[i].type != END)
		{
			ft_free((void **)&(data->tokens[i].str));
			i++;
		}
		ft_free((void **)&(data->tokens));
	}
}

static void	ms_reset_heredoc(t_data *data)
{
	if (!data)
		return ;
	data->heredoc_enabled = 0;
	data->heredoc_delimiter = NULL;
	if (data->heredoc_fd != -1)
		close(data->heredoc_fd);
	data->heredoc_fd = -1;
	unlink(HEREDOC_TMP);
}

void	ms_reset_prompt(t_data *data)
{
	if (!data)
		return ;
	ft_free((void **)&(data->line));
	ms_reset_tokens(data);
	ms_reset_cmds(data);
	ms_reset_heredoc(data);
}
