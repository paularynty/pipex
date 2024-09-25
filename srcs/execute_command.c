/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:35:45 by prynty            #+#    #+#             */
/*   Updated: 2024/09/25 16:57:45 by prynty           ###   ########.fr       */
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

static char	*find_path(char **envp, char **split_cmd)
{
	char	**envp_paths;
	char	*cmd_path;

	if (ft_strchr(*split_cmd, '/'))
	{
		if (access(*split_cmd, F_OK) == 0)
			return (ft_strdup(*split_cmd));
		else
			cmd_error(split_cmd, NO_FILE_OR_DIR, TRUE);
	}
	envp_paths = get_envp_path(envp, split_cmd);
	cmd_path = get_cmd_path(envp_paths, *split_cmd);
	free_array(&envp_paths);
	return (cmd_path);
}

static int	exec_error(t_pipex *pipex, char *path, char **cmd)
{
	if (!access(cmd[0], F_OK) && !access(cmd[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(cmd[0], '/'))
		{
			cmd_error(cmd, "Is a directory\n", TRUE);
			// exit(126); //cmd error overwrites exit with 127
			pipex->exitcode = 126;
		}
		else
		{
			cmd_error(cmd, "command not found\n", TRUE);
			exit(127); // should exit with 0 apparently
		}
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(path, 2);
	strerror(errno);
	ft_putchar_fd('\n', 2);
	// ft_printf_fd(2, "pipex: %s: %s\n", path, strerror(errno));
	free_array(&cmd);
	if (path)
		free(path);
	pipex->exitcode = 126;
	return (pipex->exitcode);
}

char	**split_command(char *cmd)
{
	int		wordcount;
	char	**array;

	if (!cmd)
		return (NULL);
	if (ft_isspace(cmd))
		cmd_error(&cmd, "command not found", FALSE);
	wordcount = count_words(cmd);
	array = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	array = split_word(array, cmd, wordcount, -1);
	return (array);
}

void	exec_command(t_pipex *pipex, char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path;

	// split_cmd = split_command(cmd);
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		exit(1);
	path = find_path(envp, split_cmd);
	if (!path)
		cmd_error(split_cmd, "command not found", TRUE);
	if (execve(path, split_cmd, envp) == -1)
		exec_error(pipex, path, split_cmd);
}
