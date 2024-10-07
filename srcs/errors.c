/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:01:26 by prynty            #+#    #+#             */
/*   Updated: 2024/10/07 18:30:55 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(t_pipex *pipex, char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		pipex->exitcode = 1;
	perror(msg);
	close_all(pipex);
	exit(pipex->exitcode);
}

void	cmd_error(t_pipex *pipex, char *cmd, char **cmd_array)
{
	int	exitcode;

	exitcode = errno;
	ft_putstr_fd("pipex: ", 2);
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (cmd_array)
		ft_free_array(&cmd_array);
	close_all(pipex);
	if (exitcode == EACCES || exitcode == EISDIR)
		exit(126);
	else
		exit(127);
}
