/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osterger <osterger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/06 02:44:47 by osterger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static int	ms_prompt(t_data *data)
{
	int	ret;

	data->line = ms_read_prompt();
	if (!data->line)
		return (SUCCESS);
	ret = ms_parse_line_to_tokens(data);
	if (ret != SUCCESS)
		return (ret);
	if (data->tokens[0].type == END)
		return (SUCCESS);
	ret = ms_parse_tokens_to_cmds(data);
	if (ret != SUCCESS)
		return (ret);
	if (ms_heredoc_create_tmp(data) != SUCCESS)
		return (ms_error("heredoc failed"), FAILURE);
	return (ms_exec_cmds(data));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data_value;
	t_data	*data;

	g_exit_code = SUCCESS;
	data = &data_value;
	if (ms_init(data, argc, argv, envp) != SUCCESS)
		ms_error_exit(data, "initialization failed", FAILURE);
	while (1)
	{
		g_exit_code = ms_prompt(data);
		ms_reset_prompt(data);
		ms_debug_exit_code(g_exit_code);
	}
	ms_reset(data);
	return (EXIT_SUCCESS);
}
