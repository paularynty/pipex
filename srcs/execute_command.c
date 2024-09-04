/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:35:45 by prynty            #+#    #+#             */
/*   Updated: 2024/09/02 13:39:48 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    *find_path(char **envp, char **split_cmd)
{
    
}

void    split_cmd(char *cmd)
{
    
}

void    exec_command(t_pipex *pipex, char *cmd)
{
    char    **split_cmd;
    char    *path;
    
    split_cmd = split_command(cmd);
    if (!split_cmd)
        exit(1);
    path = find_path(pipex->envp, split_cmd);
    if (!path)
        cmd_error(split_cmd);
    execve(path, split_cmd, pipex->envp);
    exec_error(path, split_cmd);
}