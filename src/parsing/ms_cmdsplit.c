/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:24:13 by lboulatr          #+#    #+#             */
/*   Updated: 2023/03/29 11:06:05 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(EXIT_FAILURE);
	array[count] = '\0';
	return (array);
}

static char	**ms_str(char **arr, char *str, char *set, t_split *split)
{
	ms_init_struct_split(str, split);
	while (str[split->i] != '\0')
	{
		while (ft_strchr(set, str[split->i]) && str[split->i] != '\0')
			split->i++;
		split->q_index = split->i;
		while (str[split->i] != '\0')
		{
			if ((str[split->i] == '\"' || \
			str[split->i] == '\'') && !split->quotes)
				split->quotes = str[split->i];
			else if (str[split->i] == split->quotes)
				split->quotes = 0;
			else if (ft_strchr(set, str[split->i]) && !split->quotes)
				break ;
			split->i++;
		}
		if (split->q_index >= split->len)
			arr[split->arr_index++] = "\0";
		else
			arr[split->arr_index++] = \
			ft_substr(str, split->q_index, split->i - split->q_index);
	}
	return (arr);
}

static int	ms_count_rows(char *str, char *set)
{
	int	count;
	int	quotes;

	count = 0;
	quotes = 0;
	while (*str)
	{
		if (!ft_strchr(set, *str))
		{
			count++;
			while ((!ft_strchr(set, *str) || quotes) && *str)
			{
				if (!quotes && (*str == '\"' || *str == '\''))
					quotes = *str;
				else if (quotes == *str)
					quotes = 0;
				str++;
			}
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
