/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_close_io_files.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:51:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/04/14 09:25:37 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_close_io_files(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (ms_fd_is_file(cmd->fd_in))
		close(cmd->fd_in);
	if (ms_fd_is_file(cmd->fd_out))
		close(cmd->fd_out);
}
