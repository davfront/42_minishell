/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/11 13:20:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static int	ms_prompt(t_data *data)
{
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
	return (ms_exec_cmds(data));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data_value;
	t_data	*data;

	g_exit_code = EXIT_SUCCESS;
	data = &data_value;
	ms_init(data, envp);
	ms_env_list_set(&(data->env_list), "_", argv[argc - 1]);
	while (1)
	{
		g_exit_code = ms_prompt(data);
		ms_reset_prompt(data);
		ms_debug_exit_code(g_exit_code);
	}
	ms_reset(data);
	return (EXIT_SUCCESS);
}
