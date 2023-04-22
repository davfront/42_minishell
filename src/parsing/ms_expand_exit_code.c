/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_exit_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:02:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/20 22:40:54 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_expand_exit_code(t_data *data, char *copy_str, int *index)
{
	char	*before;
	char	*after;
	char	*exit_code_as_str;
	char	*expand_str;

	if (!data)
		return (NULL);
	before = ft_substr(copy_str, 0, *index);
	if (!before)
		return (NULL);
	after = &copy_str[*index + 2];
	exit_code_as_str = ft_itoa(data->exit_code);
	if (!exit_code_as_str)
		return (ft_free((void **)&before), NULL);
	expand_str = ms_join3(before, exit_code_as_str, after);
	if (!expand_str)
	{
		ft_free((void **)&before);
		ft_free((void **)&exit_code_as_str);
		return (NULL);
	}
	(*index) += ft_strlen(exit_code_as_str);
	ft_free((void **)&before);
	ft_free((void **)&exit_code_as_str);
	return (expand_str);
}
