/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:53 by prynty            #+#    #+#             */
/*   Updated: 2024/08/27 14:12:32 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	ft_get_rows(char const *str, char chr)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == chr)
			i++;
		if (str[i] != '\0')
			rows++;
		while (str[i] && str[i] != chr)
				i++;
	}
	return (rows);
}

char	**ft_split(char const *str, char chr)
{
	char	**array;
	char	*wordstart;
	int		i;

	array = (char **)malloc(sizeof(char *) * (ft_get_rows(str, chr) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != chr)
		{
			wordstart = (char *)str;
			while (*str && *str != chr)
				str++;
			array[i] = ft_substr(wordstart, 0, str - wordstart);
			if (!**array)
				return (ft_free(array));
			i++;
		}
		else
			str++;
	}
	array[i] = NULL;
	return (array);
}
