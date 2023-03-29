/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 18:05:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cmd_args;
	int		exit_code;
	t_list	*env_list;

	(void)argc;
	(void)argv;
	env_list = NULL;
	ms_env_list_init(&env_list, envp);
	while (1)
	{
		exit_code = 0;
		line = readline("\033[1;36mminishell> \033[0m");
		add_history(line);
		cmd_args = ft_split(line, ' ');
		// todo: protect malloc
		if (ft_streq(cmd_args[0], "pwd"))
			ms_pwd();
		else if (cmd_args[0] && ft_streq(cmd_args[0], "echo"))
			ms_echo(cmd_args + 1);
		else if (ft_streq(cmd_args[0], "env"))
			ms_env(&env_list);
		else if (ft_streq(cmd_args[0], "export"))
			exit_code = ms_export(&env_list, cmd_args + 1);
		else if (ft_streq(cmd_args[0], "unset"))
			ms_unset(&env_list, cmd_args + 1);
		else if (ft_streq(cmd_args[0], "cd"))
			exit_code = ms_cd(&env_list, cmd_args + 1);
		else if (ft_streq(cmd_args[0], "exit"))
			ms_builtin_exit(&env_list, cmd_args + 1);
		else if (cmd_args[0])
			printf("%s: command not found\n", cmd_args[0]);
		if (exit_code != SUCCESS)
			printf("EXIT_FAILURE (%i)\n", exit_code);
		ft_free_split(cmd_args);
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}
