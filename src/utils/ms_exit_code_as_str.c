/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_code_as_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osterger <osterger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:32:05 by osterger          #+#    #+#             */
/*   Updated: 2023/04/05 23:32:37 by osterger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_exit_code_as_str(int exit_code)
{
	char	*res;

	res = ft_itoa(exit_code);
	if (!res)
		return (NULL);
	return (res);
}