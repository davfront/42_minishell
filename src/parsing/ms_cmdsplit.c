/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:24:13 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/25 21:17:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_get_token_length(char *str, char *set);
static int	ms_count_rows(char *str, char *set);
static char	**ms_str(char **arr, char *str, char *set, t_split *split);

char	**ms_cmdsplit(char *str, char *set)
{
	t_split	split;
	char	**array;
	int		count;

	if (!str)
		return (NULL);
	count = ms_count_rows(str, set);
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ms_str(array, str, set, &split);
	if (!array)
		return (NULL);
	array[count] = NULL;
	return (array);
}

static int	ms_get_sep_length(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strchr("><|", *str) != NULL)
		return (1);
	return (0);
}

static int	ms_get_token_length(char *str, char *set)
{
	char	quote;
	int		i;
	int		sep_len;

	if (!str)
		return (0);
	sep_len = ms_get_sep_length(str);
	if (sep_len > 0)
		return (sep_len);
	i = 0;
	quote = '\0';
	while (str[i] && (quote || \
		(!ft_strchr(set, str[i]) && !ms_get_sep_length(str + i))))
	{
		if (!quote)
		{
			if (str[i] == '\"' || str[i] == '\'')
				quote = str[i];
		}
		else if (quote == str[i])
			quote = '\0';
		i++;
	}
	return (i);
}

static char	**ms_str(char **arr, char *str, char *set, t_split *split)
{
	split->i = 0;
	split->q_index = 0;
	split->arr_index = 0;
	split->quotes = 0;
	split->len = ft_strlen(str);
	while (str[split->i] != '\0')
	{
		while (ft_strchr(set, str[split->i]) && str[split->i] != '\0')
			split->i++;
		split->q_index = split->i;
		split->i += ms_get_token_length(str + split->i, set);
		arr[split->arr_index] = \
			ft_substr(str, split->q_index, split->i - split->q_index);
		if (!arr[split->arr_index])
		{
			ft_free_split(arr);
			arr = NULL;
			return (NULL);
		}
		split->arr_index++;
	}
	return (arr);
}

static int	ms_count_rows(char *str, char *set)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (!ft_strchr(set, *str))
		{
			count++;
			str += ms_get_token_length(str, set);
		}
		else
			str++;
	}
	return (count);
}
