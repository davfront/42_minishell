/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strs_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:08:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 12:13:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_strs_len(char **strs)
{
	size_t	i;

	if (!strs || !*strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}
