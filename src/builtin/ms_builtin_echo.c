/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:53:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/04 13:29:56 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_builtin_echo_is_n_option(char *arg)
{
	if (!arg || ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	if (ft_strchr(arg + 2, '-'))
		return (0);
	return (1);
}

void	ms_builtin_echo(char **args)
{
	size_t	i;
	int		omit_end_line;

	if (!args)
		return ;
	omit_end_line = 0;
	while (ms_builtin_echo_is_n_option(*args))
	{
		omit_end_line = 1;
		args++;
	}
	i = 0;
	while (args[i])
	{
		if (i > 0)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (!omit_end_line)
		printf("\n");
}
