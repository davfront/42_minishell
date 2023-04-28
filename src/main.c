/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/28 16:03:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	ms_print_exit(t_data *data)
{
	ft_putstr("exit\n");
	ms_exit(data, data->exit_code);
}

static int	ms_prompt(t_data *data)
{
	int	ret;

	g_signal = 0;
	signal(SIGINT, ms_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data->line_no++;
	data->line = ms_read_prompt();
	if (g_signal == 2)
		return (g_signal = 0, 130);
	signal(SIGINT, SIG_IGN);
	if (!data->line)
		ms_print_exit(data);
	if (ms_expand(data) != SUCCESS)
		return (ms_error("parsing failed"), FAILURE);
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

	data = &data_value;
	if (ms_init(data, argc, argv, envp) != SUCCESS)
		ms_error_exit(data, "initialization failed", FAILURE);
	while (1)
	{
		data->exit_code = ms_prompt(data);
		if (g_signal == 2)
			ft_putstr_fd("\n", STDIN_FILENO);
		if (g_signal == 3)
			ft_putstr_fd("Quit\n", STDERR_FILENO);
		ms_reset_prompt(data);
		ms_debug_exit_code(data->exit_code);
	}
	ms_reset(data);
	return (EXIT_SUCCESS);
}
