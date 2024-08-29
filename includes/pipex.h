/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:32 by prynty            #+#    #+#             */
/*   Updated: 2024/08/29 18:03:55 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //for pipe()
#include <stdlib.h>
#include "../libft/libft.h"
#include <sys/wait.h> //for waitpid()
#include <fcntl.h> //for open, O_RDONLY, O_TRUNC, O_CREAT, etc.
#include <stdio.h> //for perror
#include <errno.h>
#include <string.h>

typedef struct s_pipex
{
    int     argc;
    int     exitcode;
    char    **argv;
    char    **envp;
    int     fd_in;
    int     fd_out;
    int     pipe_fd[2];
    int     fd[2];
    pid_t   pid;
}   t_pipex;

void    exec_pipex(t_pipex *pipex);