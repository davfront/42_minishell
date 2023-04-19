/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:22:06 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/07 12:00:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_read_prompt(void)
{
	char	*line;

	line = readline(PS1);
	if (line && *line && *line != ' ')
		add_history(line);
	return (line);
}
