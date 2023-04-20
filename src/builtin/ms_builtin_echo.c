/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:53:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/20 10:29:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_builtin_echo_is_n_option(char *arg)
{
	size_t	i;

	if (!arg)
		return (0);
	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i] == 'n')
		i++;
	return (!arg[i] && i >= 2);
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
			ft_printf(" ");
		ft_printf("%s", args[i]);
		i++;
	}
	if (!omit_end_line)
		ft_printf("\n");
}
