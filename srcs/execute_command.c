/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:35:45 by prynty            #+#    #+#             */
/*   Updated: 2024/09/25 13:13:14 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
			exit(127);
		}
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(path, 2);
	strerror(errno);
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

	split_cmd = split_command(cmd);
	if (!split_cmd)
		exit(1);
	path = find_path(envp, split_cmd);
	if (!path)
		cmd_error(split_cmd, "command not found", TRUE);
	// execve(path, split_cmd, envp);
	// exec_error(path, split_cmd);
	if (execve(path, split_cmd, envp) == -1)
		exec_error(pipex, path, split_cmd);
}
