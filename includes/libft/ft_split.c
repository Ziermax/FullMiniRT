/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:07:00 by atudor            #+#    #+#             */
/*   Updated: 2023/09/29 23:10:24 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_strings(const char *s, char sep)
{
	int		i;
	int		count;
	char	temp;
	int		quote;

	i = 0;
	count = 0;
	temp = sep;
	quote = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 39)
		{
			sep = 39;
			quote++;
		}
		if (s[i] != sep && (s[i + 1] == sep || s[i + 1] == '\0'))
			count++;
		i++;
		if (quote % 2 == 0)
			sep = temp;
	}
	return (count);
}

char	if_quotes(char *s, int i, char c, int *inside_quotes)
{
	int	sep;
	int	quote;

	sep = 0;
	quote = 0;
	if (i > 0 && s[i] == 39)
	{
		(*inside_quotes) += 1;
		sep = 0;
		quote = i + 1;
		while (s[quote] != 39)
		{
			if (s[quote] == ' ')
				sep = 1;
			quote++;
			if (s[quote] == '\0')
				break ;
		}
		if (sep == 1 && *inside_quotes % 2 != 0)
			c = 39;
	}
	return (c);
}

char	*create_substring(char *s, int positions[2], char **matrix, int *j)
{
	if (s[positions[0]] == '\'' && s[positions[1] + positions[0] - 1] == '\'')
	{
		positions[0]++;
		positions[1] -= 2;
	}
	matrix[*j] = ft_substr(s, positions[0], positions[1]);
	if (!matrix[*j])
		return (NULL);
	(*j)++;
	return (matrix[*j - 1]);
}

char	**populate_matrix(char *s, char c, char **matrix, int *inside_quotes)
{
	t_split	k;

	k.temp = c;
	k.i = 0;
	k.j = 0;
	k.positions[0] = 0;
	while (s[k.i])
	{
		c = if_quotes(s, k.i, c, inside_quotes);
		if ((k.i > 0 && s[k.i] != c && s[k.i - 1] == c)
			|| (k.i == 0 && s[0] != c))
			k.positions[0] = k.i;
		if ((s[k.i] != c && s[k.i + 1] == c)
			|| (s[k.i] != c && s[k.i + 1] == '\0'))
		{
			k.positions[1] = k.i - k.positions[0] + 1;
			if (!create_substring(s, k.positions, matrix, &k.j))
				return (free_matrix(matrix, k.j));
		}
		if (*inside_quotes % 2 == 0)
			c = k.temp;
		k.i++;
	}
	matrix[k.j] = NULL;
	return (matrix);
}

char	**ft_split(char *s, char c)
{
	char	**matrix;
	int		inside_quotes;

	inside_quotes = 0;
	matrix = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (matrix == NULL)
		return (NULL);
	return (populate_matrix(s, c, matrix, &inside_quotes));
}

/*int main()
{
	char **splitted;

	splitted = ft_split("hola que tal", ' ');
	if (!splitted)
		return NULL;
	
	int i;
	i = 0;
	while(splitted[i])
	{
		printf("%s\n", splitted[i]);
		i++;
	}
}*/
