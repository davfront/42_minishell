/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand2_exit_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:02:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/21 10:13:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_expand2_exit_code_here(t_data *data, char **str, \
	size_t *dollar_i)
{
	char	*value;

	if (!*str || ft_strlen(*str) < (*dollar_i + 1) + 1)
		return (FAILURE);
	value = ft_itoa(data->exit_code);
	if (!value)
		return (FAILURE);
	if (ms_replace_keyword(str, *dollar_i, 2, value) != SUCCESS)
		return (ft_free((void **)&value), FAILURE);
	*dollar_i += ft_strlen(value);
	ft_free((void **)&value);
	return (SUCCESS);
}

int	ms_expand2_exit_code(t_data *data, char **s)
{
	size_t	i;
	char	quote;

	quote = '\0';
	i = 0;
	while (*s && (*s)[i])
	{
		if ((*s)[i] == '\'' || (*s)[i] == '"')
		{
			if (!quote)
				quote = (*s)[i];
			else if ((*s)[i] == quote)
				quote = '\0';
		}
		if (quote != '\'' && ft_strncmp((*s) + i, "$?", 2) == 0)
		{
			if (ms_expand2_exit_code_here(data, s, &i) != SUCCESS)
				return (FAILURE);
		}
		else
			i++;
	}
	return (SUCCESS);
}
