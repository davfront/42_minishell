/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 14:56:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static int	ms_prompt(t_data *data)
{
	char	**cmd_args;
	int		ret;

	data->line = ms_read_prompt();
	if (!data->line)
		return (SUCCESS);
	data->tokens = ms_parser(data->line);
	ms_debug_tokens(data);
	if (!data->tokens)
		return (FAILURE);
	if (!data->tokens[0])
		return (SUCCESS);
	ret = ms_parse_tokens(data);
	ms_debug_cmds(data);
	if (ret != SUCCESS)
		return (ret);
	cmd_args = data->tokens;
	if (ms_is_builtin_cmd(cmd_args[0]))
		return (ms_builtin_cmd(data, cmd_args));
	else if (cmd_args[0])
	{
		ft_printf("%s: command not found\n", cmd_args[0]);
		return (CMD_NOT_FOUND);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data_value;
	t_data	*data;

	g_exit_code = EXIT_SUCCESS;
	data = &data_value;
	ms_init(data, envp);
	while (argc && argv)
	{
		g_exit_code = ms_prompt(data);
		ms_reset_prompt(data);
		ms_debug_exit_code(g_exit_code);
	}
	ms_reset(data);
	return (EXIT_SUCCESS);
}
