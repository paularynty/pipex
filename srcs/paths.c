/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:31:46 by prynty            #+#    #+#             */
/*   Updated: 2024/10/07 19:05:21 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**get_envp_path(char **envp)
{
	char	**envp_path;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
	{
		errno = ENOENT;
		return (NULL);
	}
	envp_path = ft_split(*envp + 5, ':');
	if (!envp_path)
		return (NULL);
	return (envp_path);
}

static char	*get_full_path(char **envp_path, char *cmd)
{
	char	*temp_path;
	char	*full_path;

	while (*envp_path)
	{
		temp_path = ft_strjoin(*envp_path, "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		envp_path++;
	}
	return (NULL);
}

static char	*get_cmd_path(t_pipex *pipex, char *cmd, char **cmd_array)
{
	char	*cmd_path;
	char	**envp_path;

	if (ft_strchr(&cmd[0], '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
		{
			errno = ENOENT;
			cmd_error(pipex, cmd, cmd_array);
		}
	}
	envp_path = get_envp_path(pipex->envp);
	if (!envp_path)
		return (NULL);
	cmd_path = get_full_path(envp_path, &cmd[0]);
	ft_free_array(&envp_path);
	return (cmd_path);
}

void	exec_command(t_pipex *pipex, int i)
{
	char		**cmd;
	char		*cmd_path;

	cmd = ft_split(pipex->argv[i], ' ');
	if (!cmd || !cmd[0] || ft_isspace(pipex->argv[i]))
		cmd_error(pipex, pipex->argv[i], cmd);
	cmd_path = get_cmd_path(pipex, cmd[0], cmd);
	if (!cmd_path)
		check_access(pipex, cmd[0], cmd);
	check_access(pipex, cmd_path, cmd);
	execve(cmd_path, cmd, pipex->envp);
	free(cmd_path);
	cmd_error(pipex, cmd[0], cmd);
}
