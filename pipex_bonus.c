/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:24:27 by prynty            #+#    #+#             */
/*   Updated: 2024/08/27 14:29:00 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static inline void  return_exit_code(t_pipex *pipex)
{
    int exitcode;
    
    exitcode = (pipex->exitcode & 0xff00) >> 8;
    exit (exitcode);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.exitcode = 0;
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit (1);
	}
    if (!ft_strcmp(argv[1], "here_doc"))
        //heredoc func here
	return_exit_code(&pipex);
}