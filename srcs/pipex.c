/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:07:42 by prynty            #+#    #+#             */
/*   Updated: 2024/08/28 15:13:52 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static inline void	return_exit_code(t_pipex *pipex)
{
    int exitcode;
    
    exitcode = (pipex->exitcode & 0xff00) >> 8;
    exit (exitcode);
}

// void	parent_process(char **argv, int *pipe_fd, char **envp)
// {
// 	int	fd;

// 	fd = open_file(argv[4], 1);
// 	dup2(fd, 1);
// 	dup2(pipe_fd[0], 0);
// 	close(pipe_fd[1]);
// 	//execute(pipex->argv[2], pipex->envp)
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pipe_fd[2];
	pid_t	pid;

	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.exitcode = 0;
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit (1);
	}
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Pipe failed", 2);
		exit (-1);
	}
	if (pid == -1)
		exit (-1);
	// if (!pid)
	// 	child_process(pipex.argv, pipe_fd, pipex.envp);
	// parent_process(pipex.argv, pipe_fd, pipex.envp);
	return_exit_code(&pipex);
}
