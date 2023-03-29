/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 20:18:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cmd_args;
	t_list	*env_list;

	(void)argc;
	(void)argv;
	env_list = NULL;
	ms_env_list_init(&env_list, envp);
	g_exit_code = EXIT_SUCCESS;
	while (1)
	{
		line = readline("\033[1;36mminishell> \033[0m");
		add_history(line);
		cmd_args = ft_split(line, ' ');
		// todo: protect malloc
		if (ms_is_builtin_cmd(cmd_args[0]))
			g_exit_code = ms_builtin_cmd(&env_list, cmd_args);
		else if (cmd_args[0])
			printf("%s: command not found\n", cmd_args[0]);
		if (g_exit_code != SUCCESS)
			printf("EXIT_FAILURE (%i)\n", g_exit_code);
		ft_free_split(cmd_args);
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}
