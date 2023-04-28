/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_sigint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:21:38 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/28 03:40:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	ms_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		rl_on_new_line();
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
