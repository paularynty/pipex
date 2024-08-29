/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:15:35 by prynty            #+#    #+#             */
/*   Updated: 2024/08/29 18:38:23 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    open_infile(t_pipex *pipex, int *fd)
{
    pipex->fd_in = open(pipex->argv[1], O_RDONLY);
    if (pipex->fd_in == -1)
    {
        // strerror(errno);
        //ft_printf_fd(2, "%s: %s: %s\n", "pipex", pipex->argv[1], strerror(errno));
        close (fd[1]);
        exit (1);
    }
}

void    open_outfile(t_pipex *pipex, int *prev_fd)
{
    pipex->fd_out = open(pipex->argv[pipex->argc -1], O_CREAT | O_RDWR 
        | O_TRUNC, 0644);
    if (pipex->fd_out == -1)
    {
        //ft_printf_fd(2, "%s: %s: %s\n", "pipex", pipex->argv[pipex->argc -1], strerror(errno));
        close(prev_fd[0]);
        exit (1);
    }
}


static void create_pipe_fork(pid_t *pid, int *fd)
{
    t_pipex *pipex;
    
    if (pipe(pipex->pipe_fd) == -1)
    {
        perror("Pipe failed\n");
        exit (1);
    }
    pipex->pid = fork();
    if (pipex->pid == -1)
    {
        close(pipex->pipe_fd[0]);
        close(pipex->pipe_fd[1]);
        perror("Fork failed\n");
        exit (1);
    }
}

static  void    first_cmd(t_pipex *pipex)
{
    if (pipex->pid == 0)
    {
        close(pipex->pipe_fd[0]);
        open_infile(pipex, pipex->pipe_fd);
    }
    else
        close(pipex->pipe_fd[1]);
}

// static  void    last_cmd(t_pipex *pipex)
// {
//     if (pipex->pid == 0)
//     {
//         open_outfile(pipex, prev_fd)
//     }
    
// }

void    exec_pipex(t_pipex *pipex)
{
    pid_t   pid;

    pid = pipex->pid;
    create_pipe_fork(&pid, pipex->pipe_fd);
    first_cmd(pipex);
    // last_cmd(pipex);
}