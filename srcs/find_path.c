/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:41:38 by prynty            #+#    #+#             */
/*   Updated: 2024/09/10 16:09:30 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**get_envp_path(char **envp, char **cmd)
{
	char	**split_envp;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		cmd_error(cmd, NO_FILE_OR_DIR, TRUE);
	split_envp = ft_split(*envp + 5, ':');
	return (split_envp);
}

static char	*join_cmd_path(char *envp_path, char *cmd)
{
	char	*cmd_dir;
	char	*joined_cmd_path;

	cmd_dir = ft_strjoin(envp_path, "/");
	if (!cmd_dir)
		return (NULL);
	joined_cmd_path = ft_strjoin(cmd_dir, cmd);
	free(cmd_dir);
	return (joined_cmd_path);
}

static char	*get_cmd_path(char **envp_paths, char *cmd)
{
	char	*cmd_path;

	while (*envp_paths)
	{
		cmd_path = join_cmd_path(*(envp_paths++), cmd);
		if (!cmd_path || access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*find_path(char **envp, char **split_cmd)
{
	char	**envp_paths;
	char	*cmd_path;
	char	*dup_cmd;

	if (ft_strchr(*split_cmd, '/'))
	{
		if (access(*split_cmd, F_OK) == 0)
			//return (ft_strdup(split_cmd));
		{
			dup_cmd = ft_strdup(*split_cmd);
			return (dup_cmd);
		}
		else
			cmd_error(split_cmd, NO_FILE_OR_DIR, TRUE);
	}
	envp_paths = get_envp_path(envp, split_cmd);
	cmd_path = get_cmd_path(envp_paths, *split_cmd);
	free_array(&envp_paths);
	return (cmd_path);
}
