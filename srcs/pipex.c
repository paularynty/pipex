/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:45:27 by prynty            #+#    #+#             */
/*   Updated: 2024/10/05 16:32:23 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	check_args(t_pipex *pipex)
{
	if (pipex->argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(1);
	}
}

static void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->exitcode = 0;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
}

static int	run_pipex(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipex->pipe_fd) == -1)
		exit_error(pipex, "Pipe failed");
	pid1 = fork();
	if (pid1 < 0)
		exit_error(pipex, "First child fork failed");
	if (pid1 == 0)
	{
		open_file(pipex, FIRST);
		dup_close(pipex, FIRST);
        exec_command(pipex, FIRST);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit_error(pipex, "Second child fork failed");
	if (pid2 == 0)
	{
		open_file(pipex, SECOND);
		dup_close(pipex, SECOND);
        exec_command(pipex, SECOND);
	}
	close_all(pipex);
	return (wait_for_children(pid1, pid2));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	
	init_struct(&pipex, argc, argv, envp);
	check_args(&pipex);
	pipex.exitcode = run_pipex(&pipex);
	close_all(&pipex);
	return (pipex.exitcode);
}
