/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:58:45 by prynty            #+#    #+#             */
/*   Updated: 2024/10/07 18:59:06 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_access(t_pipex *pipex, char *cmd, char **cmd_array)
{
	int	is_dir;

	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			errno = ENOENT;
		else
			errno = 0;
		cmd_error(pipex, cmd, cmd_array);
	}
	is_dir = open(cmd, __O_DIRECTORY);
	if (is_dir >= 0)
	{
		close(is_dir);
		if (cmd[ft_strlen(cmd) - 1] == '/')
			errno = EISDIR;
		else
			errno = 0;
		cmd_error(pipex, cmd, cmd_array);
	}
	if (access(cmd, X_OK) == -1)
	{	
		errno = EACCES;
		cmd_error(pipex, cmd, cmd_array);
	}
}

int	wait_for_children(t_pipex *pipex, pid_t second_child)
{
	int	status;
	int	retval;
	int	wait_count;

	wait_count = 2;
	while (wait_count > 0)
	{
		retval = waitpid(-1, &status, 0);
		if (retval == -1)
		{
			exit_error(pipex, "waitpid failed");
			break ;
		}
		wait_count--;
		if (retval == second_child && WIFEXITED(status))
			pipex->exitcode = WEXITSTATUS(status);
	}
	return (pipex->exitcode);
}

void	close_all(t_pipex *pipex)
{
	if (pipex->fd_in >= 0)
		close(pipex->fd_in);
	if (pipex->fd_out >= 0)
		close(pipex->fd_out);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

void	open_file(t_pipex *pipex, int first_or_second)
{
	if (first_or_second == FIRST)
	{
		pipex->fd_in = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd_in == -1)
			exit_error(pipex, pipex->argv[1]);
	}
	if (first_or_second == SECOND)
	{
		pipex->fd_out = open(pipex->argv[4], O_CREAT | O_WRONLY
				| O_TRUNC, 0644);
		if (pipex->fd_out == -1)
			exit_error(pipex, pipex->argv[4]);
	}
}

void	dup_close(t_pipex *pipex, int first_or_second)
{
	if (first_or_second == FIRST)
	{
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1
			|| dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			exit_error(pipex, "dup2 failed on first child");
	}
	else if (first_or_second == SECOND)
	{
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1
			|| dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			exit_error(pipex, "dup2 failed on second child");
	}
	close_all(pipex);
}
