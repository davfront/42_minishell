/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/24 11:22:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	**cmd_args;

	while (1)
	{
		line = readline("\033[1;36mminishell> \033[0m");
		add_history(line);
		cmd_args = ft_split(line, ' ');
		// todo: protect malloc
		if (ft_streq(cmd_args[0], "pwd"))
			ms_pwd();
		else if (cmd_args[0] && ft_streq(cmd_args[0], "echo"))
			ms_echo(cmd_args + 1);
		else
			printf("line = %s\n", line);
		ft_free_split(cmd_args);
		free(line);
	}
	free(line);
	return (0);
}
