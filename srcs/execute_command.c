/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:35:45 by prynty            #+#    #+#             */
/*   Updated: 2024/09/07 19:58:50 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp, char **split_cmd)
{
}

char	**split_command(char *cmd)
{
	int		wordcount;
	char	**array;

	if (!cmd)
		return (NULL);
	if (ft_isspace(cmd))
		cmd_error(&cmd, "Command not found", 0);
	wordcount = count_words(cmd);
	array = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	array = split_word(cmd, array, wordcount, -1);
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
		cmd_error(split_cmd);
	execve(path, split_cmd, pipex->envp);
	exec_error(path, split_cmd);
}
