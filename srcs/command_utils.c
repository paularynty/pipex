/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:15:35 by prynty            #+#    #+#             */
/*   Updated: 2024/09/10 16:30:48 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	skip_quotes(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] != quote)
	{
		ft_printf_fd(2, "pipex: Missing %c\n", quote);
		exit(1);
	}
	return (i);
}

static int	skip_word(char *str, int i)
{
	while (str[i] && str[i] != 32 && str[i] != 34 && str[i] != 39)
	{
		if (str[i] == 92 && str[i + 1] != '\0') //92 == backslash, if doesn't work just put if str[i] == '\\'
			i += 2;
		else
			i++;
	}
	return (i);
}

int	count_words(char *cmd)
{
	size_t	i;
	size_t	wordcount;

	i = 0;
	wordcount = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			wordcount++;
			i = skip_quotes(cmd, i) + 1;
		}
		else if (cmd[i] != 32)
		{
			wordcount++;
			i = skip_word(cmd, i);
		}
		else
			i++;
	}
	return (wordcount);
}

static char	*extract_word(char *cmd, int len)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		if ((cmd[0] == 34 || cmd[0] == 39) && cmd[i] == cmd[0])
			i++;
		else if (cmd[0] != 32 && cmd[0] != 34 && cmd[0] != 39)
			i++;
		else
		{
			if (cmd[0] != 34 && cmd[0] != 39 && cmd[i] == 92)
				i++;
			word[j++] = cmd[i++];
		}
	}
	word[j] = '\0';
	return (word);
}

char	**split_word(char **array, char *cmd, int wordcount, int order)
{
	int		i;
	char	quote;

	while (++order < wordcount)
	{
		while (*cmd == 32)
			cmd++;
		i = 0;
		quote = *cmd;
		if (*cmd == 34 || *cmd == 39)
			while (cmd[++i] != quote)
				;
		else
			i = skip_word(cmd, 0);
		array[order] = extract_word(cmd, i);
		if (!array[order])
		{
			free_array(&array);
			return (NULL);
		}
		if (*cmd == 34 || *cmd == 39)
			i++;
		cmd = cmd + i;
	}
	return (array);
}
