/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:32 by prynty            #+#    #+#             */
/*   Updated: 2024/10/06 19:48:41 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0

# define FIRST 2
# define SECOND 3

typedef struct s_pipex
{
	int				argc;
	char			**argv;
	char			**envp;
	int				exitcode;
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
}	t_pipex;

//error_handling.c
void	free_array(char ***str);
void	exit_error(t_pipex *pipex, char *msg);
void	cmd_error(t_pipex *pipex, char *cmd, char **cmd_array);

//paths.c
void	exec_command(t_pipex *pipex, int i);

//utils.c
void	check_access(t_pipex *pipex, char *cmd, char **cmd_array);
int		wait_for_children(t_pipex *pipex, pid_t pid1, pid_t pid2);
void	close_all(t_pipex *pipex);
void	open_file(t_pipex *pipex, int first_or_second);
void	dup_close(t_pipex *pipex, int first_or_second);

#endif