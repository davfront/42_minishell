/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 12:45:32 by dapereir         ###   ########.fr       */
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
		else
			printf("line = %s\n", line);
		ft_free_split(cmd_args);
		free(line);
	}
	free(line);
	return (0);
}
