/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:36:26 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/11 14:17:40 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_content_len(int index, char *str)
{
	int		count;

	count = 0;
	while (str[index])
	{
		index++;
		count++;
	}
	return (count);
}

int	ms_count_var(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || \
			!ms_is_quote(str[i + 1]) || str[i + 1] == '?' ))
		{
			if (ms_dollar_is_valid(str[i + 1]))
				size++;
		}
		i++;
	}
	return (size);
}

int	ms_char_print(char c)
{
	if (c == '%' || c == '^' || \
		c == '+' || c == '=' || \
		c == ' ' || c == '~' || \
		c == ':' || c == '\"' || \
		c == '\'' || c == '\0')
		return (1);
	return (0);
}

int	ms_char_nprint(char c)
{
	if (c == '!' || c == '@' || c == '#' || c == '&' || \
		c == '*' || c == '(' || c == ')' || c == '-' || \
		c == '_' || c == '{' || c == '}' || c == '[' || \
		c == ']' || c == ';' || c == ',' || c == '.' || \
		c == '|' || c == '/' || c == '|' || c == '$' || c == '\\')
		return (1);
	return (0);
}

int	ms_dollar_is_valid(char c)
{
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '?' || c == '!')
		return (1);
	if (ms_char_print(c) == 0)
		return (1);
	if (ft_isalpha(c) == 1)
		return (1);
	if (ms_is_quote(c) == 1)
		return (1);
	return (0);
}
