/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_dup2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:43:00 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/09 17:10:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_dup2(t_data *data, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		ms_error_exit(data, "dup2 failed", FAILURE);
	close(fd1);
}
