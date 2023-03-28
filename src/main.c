/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:16:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/28 15:20:13 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	//char	**cmd_args;

	while (1)
	{
		line = readline("\033[1;36mminishell> \033[0m");
		if (ft_strlen(line) > 0)
			add_history(line);
		ms_parser(line);
		free(line);
	}
	free(line);
	return (0);
}
