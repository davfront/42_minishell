/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_is_llong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/29 17:39:11 by dapereir         ###   ########.fr       */
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
	char	max_str[20];
	char	*start;
	char	*end;
	size_t	len;
	int		is_negative;
	int		is_overflowed;

	if (!ms_str_llong_parse(s, &is_negative, &start, &end))
		return (0);
	len = end - start;
	ft_memcpy(max_str, "9223372036854775807", 20);
	// todo : use LLONG_MAX instead
	is_overflowed = (len > ft_strlen(max_str) \
		|| (len == ft_strlen(max_str) \
		&& ft_strncmp(start, max_str, len) > is_negative));
	return (!is_overflowed);
}
