/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:58:45 by prynty            #+#    #+#             */
/*   Updated: 2024/10/05 16:32:29 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


int wait_for_children(pid_t pid1, pid_t pid2)
{
    int status;
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (0);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

void	close_all(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	close_pipes(pipex);
}

void open_file(t_pipex *pipex, int first_or_second)
{
	if (first_or_second == FIRST)
	{
		pipex->infile = open(pipex->argv[1], O_RDONLY);
		if (pipex->infile < 0)
			exit_error(pipex, pipex->argv[1]);
	}
	if (first_or_second == SECOND)
	{
		pipex->outfile = open(pipex->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			exit_error(pipex, pipex->argv[4]);
	}
}

void	dup_close(t_pipex *pipex, int first_or_second)
{
	if (first_or_second == FIRST)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1 || dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			exit_error(pipex, "Dup2 failed on first child");
	}
	else if (first_or_second == SECOND)
	{
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1 || dup2(pipex->outfile, STDOUT_FILENO) == -1)
			exit_error(pipex, "Dup2 failed on second child");
	}
	close_all(pipex);
}
