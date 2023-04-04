/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:09:23 by lboulatr          #+#    #+#             */
/*   Updated: 2023/04/04 13:25:28 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_change_line(char *str, int i, t_list *env);
static char	*ms_cut_line(char *str, int i, char *home);
static char	*ms_get_home(t_list *env);

char	*ms_tilde(char *str, t_list *env)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '~' && str[i - 1] == ' ' && (str[i + 1] == ' ' || \
					str[i + 1] == '/' || \
                    str[i + 1] == '\0' || str[i + 1] == ':'))
			str = ms_change_line(str, i, env);
		i++;
	}
	return (str);
}

static char	*ms_change_line(char *str, int i, t_list *env)
{
	char	*home;

	home = ms_get_home(env);
	if (!home)
		return (NULL);
	home = ms_cut_line(str, i, home);
	if (!home)
		return (NULL);
	return (home);
}

static char	*ms_cut_line(char *str, int i, char *home)
{
	char	*tmp;
	char	*before;
	char	*after;

	tmp = ft_strdup(str);
	if (!tmp)
		exit(EXIT_FAILURE);
	before = ft_substr(tmp, 0, i);
	if (!before)
		exit(EXIT_FAILURE);
	after = &tmp[i + 1];
	home = ft_strjoin(before, home);
	if (!home)
		exit(EXIT_FAILURE);
	home = ft_strjoin(home, after);
	if (!home)
		exit(EXIT_FAILURE);
	free(before);
	free(tmp);
	return (home);
}

static char	*ms_get_home(t_list *env)
{
	t_list	*head;
	t_env	*tmp;
	char	*home;

	head = env;
	while (head->next != NULL)
	{
		tmp = (t_env *)head->content;
		if (ft_streq("HOME", tmp->label) == 1)
		{
			home = ft_strdup(tmp->value);
			if (!home)
				exit(EXIT_FAILURE);
			return (home);
		}
		head = head->next;
	}
	return (NULL);
}
