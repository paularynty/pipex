/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:01:26 by prynty            #+#    #+#             */
/*   Updated: 2024/10/05 16:32:21 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(char ***str)
{
	size_t	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] != NULL)
			free((*str)[i++]);
		free(*str);
		*str = NULL;
	}
}

void	exit_error(t_pipex *pipex, char *msg)
{
	pipex->exitcode = 0;
	ft_putstr_fd("pipex: ", 2);
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
	{
		perror(msg);
		pipex->exitcode = 1;
	}
	else
		perror(msg);
	close_all(pipex);
	exit(pipex->exitcode);
}

void	exit_cmd_error(t_pipex *pipex, char *cmd, char **cmd_array)
{
	int	error;

	error = errno;
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(cmd);
	}
	else
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (cmd_array)
		free_array(&cmd_array);
	if (cmd && ft_strchr(cmd, '/'))
		free(cmd);
	close_all(pipex);
	if (error == EACCES || error == EISDIR)
		exit(126);
	else
		exit(127);
}
