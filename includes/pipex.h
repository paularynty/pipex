/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:32 by prynty            #+#    #+#             */
/*   Updated: 2024/09/07 19:51:37 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //for pipe()
# include <stdlib.h>
# include "../libft/libft.h"
# include <sys/wait.h> //for waitpid()
# include <fcntl.h> //for open, O_RDONLY, O_TRUNC, O_CREAT, etc.
# include <stdio.h> //for perror
# include <errno.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define NO_FILE_OR_DIR "No such file or directory"

typedef enum e_errors
{
	hehe,
	haha,
	hoho,
}	t_errors;

typedef struct s_pipex
{
	char			**argv;
	char			**envp;
	int				argc;
	int				exitcode;
	int				fd_in; //can replace with stdin_fileno
	int				fd_out; //can replace with stdout_fileno
	int				pipe_fd[2];
	int				fd[2];
	pid_t			pid;
}	t_pipex;

void	exec_pipex(t_pipex *pipex);
int		open_infile(t_pipex *pipex, int *fd);
int		open_outfile(t_pipex *pipex, int *prev_fd);
void	exec_command(t_pipex *pipex, char *cmd);

#endif