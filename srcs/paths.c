/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:31:46 by prynty            #+#    #+#             */
/*   Updated: 2024/10/05 16:41:42 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_full_path(char **paths, const char *cmd)
{
	char	*temp_path;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*get_env(t_pipex *pipex)
{
	char	*path_env;
	int		i;

	i = 0;
	while (pipex->envp[i] != NULL)
	{
		if (ft_strncmp(pipex->envp[i], "PATH=", 5) == 0)
		{
			path_env = pipex->envp[i] + 5;
			break ;
		}
		i++;
	}
	if (pipex->envp[i] == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	return (path_env);
}

static char	*get_path(t_pipex *pipex, const char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	path_env = get_env(pipex);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = get_full_path(paths, cmd);
	free_array(&paths);
	return (full_path);
}

static void	check_access(t_pipex *pipex, char *cmd, char **cmd_arr)
{
	int	is_dir;

	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			errno = ENOENT;
		else
			errno = 0;
		exit_cmd_error(pipex, cmd, cmd_arr);
	}
	is_dir = open(cmd, __O_DIRECTORY);
	if (is_dir != -1)
	{
		close(is_dir);
		if (cmd[ft_strlen(cmd) - 1] == '/')
			errno = EISDIR;
		else
			errno = 0;
		exit_cmd_error(pipex, cmd, cmd_arr);
	}
	if (access(cmd, X_OK) == -1)
	{	
		errno = EACCES;
		exit_cmd_error(pipex, cmd, cmd_arr);
	}
}

static char	*is_cmd_path(t_pipex *pipex, char *cmd, char **cmd_array)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		errno = ENOENT;
		ft_putstr_fd("pipex: ", 2);
		perror(cmd);
		free_array(&cmd_array);
		close_all(pipex);
		exit(127);
	}
}

void exec_command(t_pipex *pipex, int i)
{
    char    **cmd;
    char    *cmd_path;
    
    cmd = ft_split(pipex->argv[i + 2], ' ');
	if (!cmd || !cmd[0] || ft_isspace(pipex->argv[i + 2]))
        exit_cmd_error(pipex, pipex->argv[i + 2], cmd);
    if (ft_strchr(cmd[0], '/'))
        cmd_path = is_cmd_path(pipex, cmd[0], cmd);
    else
        cmd_path = get_path(pipex, cmd[0]);
    if (!cmd_path)
        check_access(pipex, cmd[0], cmd);
    check_access(pipex, cmd_path, cmd);
    execve(cmd_path, cmd, pipex->envp);
    free(cmd_path);
    exit_cmd_error(pipex, cmd[0], cmd);
}
