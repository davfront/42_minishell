/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:53:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/22 12:23:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(char **args)
{
	size_t	i;
	int		omit_new_line;

	if (!args)
		return ;
	omit_new_line = (ft_streq(args[0], "-n"));
	i = omit_new_line;
	while (args[i])
	{
		if (i > (size_t)omit_new_line)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (!omit_new_line)
		printf("\n");
}
