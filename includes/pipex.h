/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:32 by prynty            #+#    #+#             */
/*   Updated: 2024/09/10 16:30:33 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //for pipe()
// # include <stdlib.h>
# include "../libft/libft.h"
# include <sys/wait.h> //for waitpid()
# include <sys/types.h>
# include <fcntl.h> //for open, O_RDONLY, O_TRUNC, O_CREAT, etc.
# include <stdio.h> //for perror
# include <errno.h> //for errno
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

//pipe, dup, etc
void	dup_and_close(int from_fd1, int to_fd1, int from_fd2, int to_fd2);
int		open_infile(t_pipex *pipex, int *fd);
int		open_outfile(t_pipex *pipex, int *prev_fd);
void	create_pipe_fork(pid_t *pid, int *pipe_fd);

//execution
void	exec_command(t_pipex *pipex, char *cmd);
char	**split_command(char *cmd);
char	**split_word(char **array, char *cmd, int wordcount, int order);
char	*find_path(char **envp, char **split_cmd);

//utils
int		count_words(char *cmd);

//error handling
void	cmd_error(char **cmd, char *msg, int to_free);
void	free_array(char ***str);

#endif