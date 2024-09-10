/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:34:50 by prynty            #+#    #+#             */
/*   Updated: 2024/09/10 15:26:11 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

// // void    fork_error(int *fd)
// // {
// //     close(fd[0]);
// //     close(fd[1]);
// //     perror("Last command fork failed");
// //     exit (1);
// // }

void	cmd_error(char **cmd, char *msg, int to_free)
{
	ft_printf_fd(2, "pipex: %s: %s\n", *cmd, msg);
	if (to_free)
		free_array(&cmd);
	exit(127); //tweak this according to exit code
}
// }

// void    exec_error(char *path, char *split_cmd)
// {
// }