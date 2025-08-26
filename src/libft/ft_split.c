/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:35:22 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/26 20:37:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*s = string to split | c = delimiter character.
Return an array with the strings.
Save an array of strings when split 's'. 
The array must end with a NULL pointer.*/

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
			i++;
	}
	return (words);
}

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
/*
int	main(void)
{
	char const *s = "split  ||this|for|me|||||!|";
	char c = '|';
	char **result = ft_split(s, c);
	if (result) {
		int i = 0;
		while (result[i])
		{
			printf("%s\n", result[i]);
			i++;
		}
	}
	return (0);
}

*/