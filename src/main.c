/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 12:01:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_data	data_value;
	t_data	*data;
	char	**cmd_args;

	g_exit_code = EXIT_SUCCESS;
	data = &data_value;
	ms_init(data, envp);
	while (argc && argv)
	{
		data->line = ms_read_prompt();
		data->tokens = ms_parser(data->line);
		ms_debug_tokens(data);
		cmd_args = data->tokens;
		if (ms_is_builtin_cmd(cmd_args[0]))
			g_exit_code = ms_builtin_cmd(data, cmd_args);
		else if (cmd_args[0])
			ft_printf("%s: command not found\n", cmd_args[0]);
		ms_reset_prompt(data);
		ms_debug_exit_code(g_exit_code);
	}
	ms_reset(data);
	return (EXIT_SUCCESS);
}
