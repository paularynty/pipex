/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:07:42 by prynty            #+#    #+#             */
/*   Updated: 2024/08/30 16:47:06 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static inline void	return_exit_code(t_pipex *pipex)
{
    int exitcode;
    
	exitcode = (pipex->exitcode >> 8) & 255;
    // exitcode = (pipex->exitcode & 0xff00) >> 8;
    exit (exitcode);
}

// static void	parent_process(char **argv, int *pipe_fd, char **envp)
// {
// 	int	fd;

// 	fd = open_outfile(argv[4], 1);
// 	dup2(fd, 1);
// 	dup2(pipe_fd[0], 0);
// 	close(pipe_fd[1]);
// 	//execute_command(argv[3], envp);
// }

// static void	child_process(char **argv, int *pipe_fd, char **envp)
// {
// 	int	fd;

// 	fd = open_infile(argv[1], 0);
// 	dup2(fd, 0);
// 	dup2(pipe_fd[1], 1);
// 	close(pipe_fd[0]);
// 	//execute_command(argv[2], envp);
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
	exec_pipex(&pipex);
	return_exit_code(&pipex);
}
