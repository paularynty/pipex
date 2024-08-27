/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:32 by prynty            #+#    #+#             */
/*   Updated: 2024/08/27 14:28:39 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //for pipe()
#include <stdlib.h>
#include "../libft/libft.h"
#include <sys/wait.h> //for waitpid()

typedef struct s_pipex
{
    int     argc;
    int     exitcode;
    char    **argv;
    char    **envp;
}   t_pipex;
