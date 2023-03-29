/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_exit_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:35:33 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/30 00:17:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_exit_code(int exit_code)
{
	if (!DEBUG)
		return;
	ft_printf("\033[2mexit_code: %i\n\033[0m", exit_code);
}