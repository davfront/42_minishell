/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 21:11:08 by dapereir         ###   ########.fr       */
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
		data->line = readline("\033[1;36mminishell> \033[0m");
		add_history(data->line);
		data->tokens = ft_split(data->line, ' ');
		// todo: protect malloc
		cmd_args = data->tokens;
		if (ms_is_builtin_cmd(cmd_args[0]))
			g_exit_code = ms_builtin_cmd(data, cmd_args);
		else if (cmd_args[0])
			printf("%s: command not found\n", cmd_args[0]);
		if (g_exit_code != SUCCESS)
			printf("EXIT_FAILURE (%i)\n", g_exit_code);
		ft_free_split(data->tokens);
		ft_free((void **)&(data->line));
	}
	ms_reset(data);
	return (EXIT_SUCCESS);
}
