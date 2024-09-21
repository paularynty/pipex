/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:26:13 by prynty            #+#    #+#             */
/*   Updated: 2024/09/21 14:47:00 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	dup_and_close(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
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

// int	open_infile(t_pipex *pipex, int *fd)
// {
// 	int	result;

// 	result = 0;
// 	pipex->fd_in = open(pipex->argv[1], O_RDONLY);
// 	if (pipex->fd_in == -1)
// 	{
// 	// strerror(errno);
// 		ft_printf_fd(2, "%s: %s: %s\n", "pipex", pipex->argv[1],
// 			strerror(errno));
// 		close (fd[1]);
// 		exit(1);
// 	}
// 	return (result);
// }

// int	open_outfile(t_pipex *pipex, int *prev_fd)
// {
// 	int	result;

// 	result = 0;
// 	pipex->fd_out = open(pipex->argv[pipex->argc -1], O_CREAT | O_RDWR
// 			| O_TRUNC, 0644); //0644 = owner can read/write but not execute, and group and others only read
// 	if (pipex->fd_out == -1)
// 	{
// 		ft_printf_fd(2, "%s: %s: %s\n", "pipex", pipex->argv[pipex->argc -1], strerror(errno));
// 		close(prev_fd[0]);
// 		exit(1);
// 	}
// 	return (result);
// }
