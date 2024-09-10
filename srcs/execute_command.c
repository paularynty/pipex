/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:35:45 by prynty            #+#    #+#             */
/*   Updated: 2024/09/10 16:00:32 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static inline void	exec_error(char *path, char **cmd)
{
	if (!access(cmd[0], F_OK) && !access(cmd[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(cmd[0], '/'))
		{
			cmd_error(cmd, "Is a directory", TRUE);
			exit(126); //cmd error overwrites exit with 127
		}
		else
		{
			cmd_error(cmd, "Command not found", TRUE);
			exit(127);
		}
	}
	ft_printf_fd(2, "pipex: %s, %s\n", path, strerror(errno));
	free_array(&cmd);
	if (path)
		free(path);
	exit(126);
}

char	**split_command(char *cmd)
{
	int		wordcount;
	char	**array;

	if (!cmd)
		return (NULL);
	if (ft_isspace(cmd))
		cmd_error(&cmd, "Command not found", FALSE);
	wordcount = count_words(cmd);
	array = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	array = split_word(array, cmd, wordcount, -1);
	return (array);
}

void	exec_command(t_pipex *pipex, char *cmd)
{
	char	**split_cmd;
	char	*path;

	split_cmd = split_command(cmd);
	if (!split_cmd)
		exit(1);
	path = find_path(pipex->envp, split_cmd);
	if (!path)
		cmd_error(split_cmd, "Command not found", TRUE);
	execve(path, split_cmd, pipex->envp);
	exec_error(path, split_cmd);
}
