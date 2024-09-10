/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:07:42 by prynty            #+#    #+#             */
/*   Updated: 2024/09/10 16:53:40 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	first_cmd(t_pipex *pipex, pid_t *pid)
{
	if (pid == 0)
	{
		close(pipex->pipe_fd[0]);
		open_infile(pipex, pipex->pipe_fd);
		dup_and_close(pipex->fd_in, 0, pipex->pipe_fd[1], 1);
	}
	else
		close(pipex->pipe_fd[1]);
}

static void	last_cmd(t_pipex *pipex, pid_t *pid)
{
	*pid = fork();
	if (pipex->pid == -1)
	{
		close(pipex->pipe_fd[0]);
		perror("Last command fork failed");
		exit(1);
		// fork_error(pipex->pipe_fd);
	}
	else if (pipex->pid == 0)
	{
		open_outfile(pipex, pipex->pipe_fd);
		dup_and_close(pipex->pipe_fd[0], 0, pipex->fd_out, 1);
		exec_command(pipex, pipex->argv[2]);
	}
	else
		waitpid(pipex->pid, &(pipex->exitcode), 0);
}

void	exec_pipex(t_pipex *pipex)
{
	int		pipe_fd[2];
	pid_t	pid;

	create_pipe_fork(&pid, pipe_fd);
	first_cmd(pipex, &pid);
	last_cmd(pipex, &pid);
}

static inline void	return_exit_code(t_pipex *pipex)
{
	int		exitcode;

	exitcode = (pipex->exitcode >> 8) & 255;
	exit (exitcode);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf_fd(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit(1);
	}
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.exitcode = 0;
	exec_pipex(&pipex);
	return_exit_code(&pipex);
}
