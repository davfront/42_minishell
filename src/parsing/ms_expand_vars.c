/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:02:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/28 13:41:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_parse_env_label(char *s)
{
	size_t	i;
	char	*label;

	if (!s || !*s)
		return (NULL);
	i = 0;
	while (s[i] == '_' || ft_isalpha(s[i]) || (i == 0 || ft_isdigit(s[i])))
		i++;
	if (i == 0)
		return (NULL);
	label = ft_strndup(s, i);
	return (label);
}

static int	ms_expand_var_here(char **str, t_list **env_list, \
	size_t *dollar_i)
{
	char	*dollar;
	char	*label;
	char	*value;

	if (!*str || ft_strlen(*str) < (*dollar_i + 1) + 1)
		return (FAILURE);
	dollar = *str + *dollar_i;
	if (ft_strchr("0123456789!@#&*()-_{}[];,.|/|$\\", dollar[1]))
		label = ft_strndup(dollar + 1, 1);
	else if (ft_strchr("\"\'", dollar[1]))
		label = ft_strdup("");
	else
		label = ms_parse_env_label(dollar + 1);
	if (!label)
		return (FAILURE);
	value = ms_env_list_get(env_list, label);
	if (ms_replace_keyword(str, *dollar_i, ft_strlen(label) + 1, value) \
		!= SUCCESS)
		return (ft_free((void **)&label), FAILURE);
	if (value)
		*dollar_i += ft_strlen(value);
	return (ft_free((void **)&label), SUCCESS);
}

static char	ms_update_quote(char quote, char c)
{
	if (c == '\'' || c == '"')
	{
		if (!quote)
			quote = c;
		else if (c == quote)
			quote = '\0';
	}
	return (quote);
}

int	ms_expand_vars(char **s, t_list **env_list)
{
	size_t	i;
	char	quote;

	quote = '\0';
	i = 0;
	while (*s && (*s)[i])
	{
		quote = ms_update_quote(quote, (*s)[i]);
		if (quote != '\'' && (*s)[i] == '$' && (*s)[i + 1]
			&& !ft_strchr(" \t\n^+=~:%}", (*s)[i + 1])
			&& (quote != '"' || ((*s)[i + 1] != '\'' && (*s)[i + 1] != '"'))
		)
		{
			if (ms_expand_var_here(s, env_list, &i) != SUCCESS)
				return (FAILURE);
		}
		else
			i++;
	}
	return (SUCCESS);
}
