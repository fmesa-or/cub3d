/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:35:22 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/22 21:27:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**************************************************
 * Frees allocated array in case of malloc fail. *
 * Iterates backwards freeing each string.       *
 *************************************************/
static void	*ft_delarray(char **array, int k)
{
	while (k >= 0)
	{
		sfree (array[k]);
		k -= 1;
	}
	sfree (array);
	return (NULL);
}

/**************************************************************
 * Creates individual strings from source by delimiter.      *
 * Skips delimiters and copies substrings to array slots.    *
 * Handles memory allocation for each substring.              *
 *************************************************************/
static char	**ft_gears(char **array, char *s, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i] && k < words)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		array[k] = smalloc ((j + 1) * sizeof(char));
		if (array[k] == NULL)
		{
			ft_delarray(array, k);
			return (NULL);
		}
		ft_strlcpy(array[k], &s[i], j + 1);
		i = i + j;
		k++;
	}
	array[k] = NULL;
	return (array);
}

/*************************************************
 * Counts number of words separated by delimiter.*
 * Skips consecutive delimiters between words.   *
 ************************************************/
static int	ft_count(char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
		{
			if (s[i + 1] == c)
				error_msg("Error\nJust one colon at the time.\n");
			i++;
		}
	}
	return (words);
}

/********************************************************
 * Splits string into array of substrings by delimiter.*
 * Allocates memory for array and calls helper funcs.  *
 * Returns NULL-terminated array of strings.           *
 *******************************************************/
char	**ft_split(char const *s, char c)
{
	int		words;
	char	**array;

	words = ft_count((char *)s, c);
	array = (char **)smalloc((words + 1) * sizeof(char **));
	if (array == NULL)
		return (NULL);
	array = ft_gears(array, (char *)s, c, words);
	return (array);
}
