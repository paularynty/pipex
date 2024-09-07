/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_unsigned_fd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:13:16 by prynty            #+#    #+#             */
/*   Updated: 2024/09/07 18:27:29 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr_unsigned_fd(int fd, unsigned int n)
{
	int		len;
	int		value;
	char	c;

	len = 0;
	if (n > 9)
	{
		value = ft_print_nbr_unsigned_fd(fd, (n / 10));
		if (value == -1)
			return (value);
		len += value;
	}
	c = (n % 10) + '0';
	if (ft_print_char_fd(fd, c) < 0)
		return (-1);
	len++;
	return (len);
}
