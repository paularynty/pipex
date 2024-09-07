/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:39 by prynty            #+#    #+#             */
/*   Updated: 2024/09/07 18:29:40 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str_fd(int fd, const char *str)
{
	int	i;
	int	temp;

	i = 0;
	temp = i;
	if (!str)
	{
		if (write(fd, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (str[i])
	{
		i += ft_print_char_fd(fd, str[i]);
		if (i < temp)
			return (-1);
	}
	return (i);
}
