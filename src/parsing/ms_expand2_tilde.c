/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand2_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:02:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/21 07:18:36 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_expand2_tilde_here(char **str, t_list **env_list, size_t *tilde_i)
{
	char	*value;

	if (!*str || ft_strlen(*str) < *tilde_i + 1)
		return (FAILURE);
	value = ms_env_list_get(env_list, "HOME");
	if (ms_replace_keyword(str, *tilde_i, 1, value) != SUCCESS)
		return (FAILURE);
	if (value)
		*tilde_i += ft_strlen(value);
	return (SUCCESS);
}

int	ms_expand2_tilde(char **s, t_list **env_list)
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
		if (!quote && (*s)[i] == '~')
		{
			if (ms_expand2_tilde_here(s, env_list, &i) != SUCCESS)
				return (FAILURE);
		}
		else
			i++;
	}
	return (SUCCESS);
}
