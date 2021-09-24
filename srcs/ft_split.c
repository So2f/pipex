/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-kar <soel-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:53:10 by soel-kar          #+#    #+#             */
/*   Updated: 2021/09/23 22:36:51 by soel-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		ft_count_words(const char *s, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (words);
}

char	**ft_size_words(const char *s, char c, char **dest)
{
	int i;
	int j;
	int size_word;

	i = 0;
	j = 0;
	while (s[i])
	{
		size_word = 0;
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			{
				++size_word;
				++i;
			}
			dest[j] = malloc(sizeof(char) * (size_word + 1));
			j++;
			if (!dest)
				return (NULL);
		}
		else
			i++;
	}
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**dest;

	i = 0;
	j = 0;
	if (!(dest = malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	if (!(ft_size_words(s, c, dest)))
		return (NULL);
	while (s[i] && !(k = 0))
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				dest[j][k++] = s[i++];
			dest[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	dest[j] = NULL;
	return (dest);
}