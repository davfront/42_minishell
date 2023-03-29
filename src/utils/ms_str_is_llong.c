/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_is_llong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 22:38:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_str_llong_parse(char *s, int *is_neg, char **start, char **end)
{
	if (!s || !*s)
		return (0);
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	*is_neg = (*s == '-');
	if ((*s == '-' || *s == '+') && ft_isdigit(*(s + 1)))
		s++;
	while (*s == '0' && ft_isdigit(*(s + 1)))
		s++;
	*start = s;
	while (ft_isdigit(*s))
		s++;
	*end = s;
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	if (*s)
		return (0);
	return (1);
}

int	ms_str_is_llong(char *s)
{
	char	*start;
	char	*end;
	size_t	len;
	int		is_negative;
	int		is_overflowed;

	if (!ms_str_llong_parse(s, &is_negative, &start, &end))
		return (0);
	len = end - start;
	is_overflowed = (len > ft_strlen(LLONG_MAX_STR) \
		|| (len == ft_strlen(LLONG_MAX_STR) \
		&& ft_strncmp(start, LLONG_MAX_STR, len) > is_negative));
	return (!is_overflowed);
}
