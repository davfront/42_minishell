/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:09:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 18:16:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_quoted(char *s)
{
	if (!s)
		return ;
	ft_putchar('"');
	while (*s)
	{
		if (*s == '"' || *s == '\\')
			ft_putchar('\\');
		ft_putchar(*s);
		s++;
	}
	ft_putchar('"');
}
