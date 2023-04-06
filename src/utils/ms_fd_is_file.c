/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_is_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 08:53:33 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/14 09:08:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_fd_is_file(int fd)
{
	if (fd == -1)
		return (0);
	if (fd == STDIN_FILENO)
		return (0);
	if (fd == STDOUT_FILENO)
		return (0);
	if (fd == STDERR_FILENO)
		return (0);
	return (1);
}
