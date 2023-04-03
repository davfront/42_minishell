/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:14:53 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/03 15:36:05 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	ms_free_and_exit(char *str)
{
	free(str);
	exit(EXIT_FAILURE);
}

void	ms_free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (ft_streq(array[i], "") == 0)
			free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

char	*ms_get_exit_code(int exit_code)
{
	char	*res;

	res = ft_itoa(exit_code);
	if (!res)
		exit(EXIT_FAILURE);
	return (res);
}
