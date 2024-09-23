/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:07:42 by prynty            #+#    #+#             */
/*   Updated: 2024/09/23 16:13:01 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	check_args(t_pipex *pipex)
{
	if (pipex->argc != 5)
	{
		ft_printf_fd(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		pipex->exitcode = 1;
		return (1);
	}
	return (0);
}

// static void	first_cmd(t_pipex *pipex, pid_t *pid, int *pipe_fd)
// {
// 	if (pid == 0)
// 	{
// 		close(pipe_fd[0]);
// 		open_infile(pipex, pipex->pipe_fd);
// 		dup_and_close(pipex->fd_in, 0, pipe_fd[1], 1);
// 		exec_command(pipex, pipex->argv[2]);
// 	}
// 	else
// 		close(pipe_fd[1]);
// }

// static void	last_cmd(t_pipex *pipex, pid_t *pid, int *pipe_fd)
// {
// 	*pid = fork();
// 	if (*pid == -1)
// 	{
// 		close(pipe_fd[0]);
// 		perror("Last command fork failed");
// 		exit(1);
// 	}
// 	else if (*pid == 0)
// 	{
// 		open_outfile(pipex, pipex->pipe_fd);
// 		dup_and_close(pipe_fd[0], 0, pipex->fd_out, 1);
// 		exec_command(pipex, pipex->argv[pipex->argc - 2]);
// 	}
// 	close(pipe_fd[0]);
// 	waitpid(*pid, &pipex->exitcode, 0);
// }

// static void	create_pipe_fork(pid_t *pid, int *pipe_fd)
// {
// 	t_pipex	*pipex;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Pipe failed");
// 		exit(1);
// 	}
// 	*pid = fork();
// 	if (*pid == -1)
// 	{
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		perror("Fork failed");
// 		exit(1);
// 	}
// }

// void	exec_pipex(t_pipex *pipex)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;

// 	create_pipe_fork(&pid, pipe_fd);
// 	if (pid == 0)
// 		first_cmd(pipex, &pid, pipe_fd);
// 	last_cmd(pipex, &pid, pipe_fd);
// 	while (wait(NULL) > 0)
// 		;
// }

// static void	dup_and_close(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
// {
// 	if (dup2(from_fd1, to_fd1) == -1 || dup2(from_fd2, to_fd2) == -1)
// 	{
// 		perror("Dup2 failed");
// 		close(from_fd1);
// 		close(from_fd2);
// 		exit(1);
// 	}
// 	close(from_fd1);
// 	close(from_fd2);
// }

static int	open_file(char *file, int in_or_out)
{
	t_pipex *pipex;
	int		result;

	if (in_or_out == 0)
		result = open(file, O_RDONLY, 0777);
	else if (in_or_out == 1)
		result = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (result == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n", pipex->argv[1], strerror(errno));
		close (in_or_out);
		exit(1);
	}
	return (result);
}

// static void	child(char **argv, int *pipe_fd, char **envp)
static void	child(t_pipex *pipex, char **argv, char **envp)
{
	// t_pipex	*pipex;
	int		fd;

	fd = open_file(argv[1], 0);
	// dup_and_close(fd, 0, pipe_fd[1], 1);
	dup2(fd, 0);
	dup2(pipex->fd[1], 1);
	close(pipex->fd[0]);
	exec_command(pipex, argv[2], envp);
}

// static void	parent(char **argv, int *pipe_fd, char **envp)
static void	parent(t_pipex *pipex, char **argv, char **envp)
{
	// t_pipex	*pipex;
	int		fd;
	
	fd = open_file(argv[4], 1);
	// dup_and_close(fd, 1, pipe_fd[0], 0);
	dup2(fd, 1);
	dup2(pipex->fd[0], 0);
	close(pipex->fd[1]);
	exec_command(pipex, argv[3], envp);
	// waitpid(pipex->pid, &pipex->exitcode, 0);
}

static inline int	return_exit_code(t_pipex *pipex)
{
	int	exitcode;

	exitcode = (pipex->exitcode >> 8) & 255;
	ft_printf("Process exited with exit code %d\n", exitcode);
	exit(exitcode);
}

static void	create_pipe(t_pipex *pipex, char **argv, char **envp)
{
	if (pipe(pipex->fd) < 0)
	{
		perror("Pipe failed");
		exit(1);
	}
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		child(pipex, argv, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		parent(pipex, argv, envp);
	waitpid(pipex->pid1, &pipex->status1, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
}

static void	open_files(t_pipex *pipex)
{
	pipex->fd_in = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
		ft_printf_fd(2, "pipex: %s: %s\n", pipex->argv[1], strerror(errno));
	pipex->fd_out = open(pipex->argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->fd_out < 0)
		ft_printf_fd(2, "pipex: %s: %s\n", pipex->argv[4], strerror(errno));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pipe_fd[2];
	pid_t	pid;

	pipex.exitcode = 0;
	pipex.argc = argc;
	pipex.argv = argv;
	if (check_args(&pipex))
		return (pipex.exitcode);
	open_files(&pipex);
	create_pipe(&pipex, argv, envp);
	// if (pipe(pipe_fd) == -1)
	// {
	// 	perror("Pipe failed");
	// 	exit(1);
	// }
	// pid = fork();
	// if (pid == -1)
	// {
	// 	perror("Fork failed");
	// 	exit(1);
	// }
	// if (pid == 0)
	// 	child(argv, pipe_fd, envp);
	// parent(argv, pipe_fd, envp);
	return_exit_code(&pipex);
}
