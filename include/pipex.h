/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:32 by prynty            #+#    #+#             */
/*   Updated: 2024/10/05 16:33:07 by prynty           ###   ########.fr       */
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

# define FIRST 0
# define SECOND 1

# define CMD_NOT_FOUND "command not found"
# define IS_DIR "Is a directory"
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
	int				status1;
	int				status2;
	int				infile;
	int				outfile;
	char			**cmd1;
	char			**cmd2;
	char			*cmd_path;
}	t_pipex;

// void	exec_pipex(t_pipex *pipex);
// int		open_infile(t_pipex *pipex, int *fd);
// int		open_outfile(t_pipex *pipex, int *prev_fd);

//pipe, dup, etc
// void	dup_and_close(int from_fd1, int to_fd1, int from_fd2, int to_fd2);
// int		open_infile(t_pipex *pipex, int *fd);
// int		open_outfile(t_pipex *pipex, int *prev_fd);
// void	create_pipe_fork(pid_t *pid, int *pipe_fd);

//execution
// void	exec_command(t_pipex *pipex, char *cmd, char **envp);
// char	**validate_cmd_path(t_pipex *pipex, char *cmd, char **envp);
// char	**exec_command(t_pipex *pipex, char *cmd, char **envp);
// char	**split_command(char *cmd);
// char	**split_word(char **array, char *cmd, int wordcount, int order);
// // char	*find_path(char **envp, char **split_cmd);

// //utils
// int		count_words(char *cmd);

// //error handling
// void	print_error(char *file, char *msg);
// void	cmd_error(t_pipex *pipex, char **cmd, char *msg, int to_free);
// void	cmd_error2(t_pipex *pipex, char *cmd, char **split_cmd, char *msg, int to_free);
// void	free_array(char ***str);
// void	exit_with_error(t_pipex *pipex, char *msg);
// void	exit_cmd_error(t_pipex *pipex, char *cmd, char **cmd_array);

// //validate_command.c
// static char	*create_path(char *dir, char *cmd);
// static int	find_in_paths(char **paths, char **exec_args, int *path_error);
// // static char	**search_paths(char **exec_args, char **envp, int *path_error);
// static char	**get_exec_path_more(char *command, char **envp, int *path_error);
// char	**validate_command(t_pipex *pipex, char *cmd, int *exitcode);

// //path_helpers.c
// int	is_abs_or_pwd_path(char *cmd);
// int	check_exec_access(char *cmd);
// char	**get_paths(char **envp);

//error_handling.c
void	free_array(char ***str);
void	exit_error(t_pipex *pipex, char *msg);
void	exit_cmd_error(t_pipex *pipex, char *cmd, char **cmd_array);

//paths.c
void	exec_command(t_pipex *pipex, int i);

//utils.c
int		wait_for_children(pid_t pid1, pid_t pid2);
void	close_pipes(t_pipex *pipex);
void	close_all(t_pipex *pipex);
void	open_file(t_pipex *pipex, int first_or_second);
void	dup_close(t_pipex *pipex, int first_or_second);

#endif