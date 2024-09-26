/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:34:50 by prynty            #+#    #+#             */
/*   Updated: 2024/09/26 11:36:58 by prynty           ###   ########.fr       */
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

void	print_error(char *file, char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	cmd_error(char **cmd, char *msg, int to_free)
{
	ft_printf_fd(2, "pipex: %s: %s\n", *cmd, msg);
	if (to_free)
		free_array(&cmd);
	exit(127); //tweak this according to exit code
}

// void    exec_error(char *path, char *split_cmd)
// {
// }