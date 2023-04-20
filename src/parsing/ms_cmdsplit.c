/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmdsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:24:13 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/20 06:39:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_get_token_length(char *str, char *set);
static int	ms_count_rows(char *str, char *set);
static char	**ms_str(char **arr, char *str, char *set, t_split *split);
static void	ms_init_struct_split(char *str, t_split *split);

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
	array[count] = '\0';
	return (array);
}

static int	ms_get_token_length(char *str, char *set)
{
	char	quote;
	int		i;

	if (!str)
		return (0);
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strchr("><|", *str) != NULL)
		return (1);
	i = 0;
	quote = '\0';
	while (str[i] && (quote || !ft_strchr(set, str[i])))
	{
		if (quote == str[i])
			quote = 0;
		else if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		i++;
	}
	return (i);
}

static char	**ms_str(char **arr, char *str, char *set, t_split *split)
{
	ms_init_struct_split(str, split);
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

static void	ms_init_struct_split(char *str, t_split *split)
{
	split->i = 0;
	split->q_index = 0;
	split->arr_index = 0;
	split->quotes = 0;
	split->len = ft_strlen(str);
}
