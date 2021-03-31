/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:15:31 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/26 15:23:54 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_word(char const *s, char c)
{
	int		x;
	int		wrd;

	x = 0;
	wrd = 0;
	while (s[x])
	{
		if (s[x] == c)
		{
			if (s[x + 1] == c)
				wrd++;
			while (s[x] == c && s[x])
				x++;
		}
		else
		{
			while (s[x] != c && s[x])
				x++;
			wrd++;
		}
	}
	return (wrd);
}
 
static char		*fill_string(char const *s, char c, char *t, int i)
{
	int		x;
	int		z;
	int		a;

	x = i;
	a = i;
	z = 0;
	while (s[x] == c && s[x])
		x++;
	while (s[x] != c && s[x])
		x++;
	if (!(t = malloc((x - i + 1) * sizeof(char))))
		return (NULL);
	while (z < (x - i) && s[a] != '\0')
	{
		t[z] = s[a];
		z++;
		a++;
	}
	t[z] = '\0';
	return (t);
}

static int		set_index(char const *s, char c, int i, int z)
{
	int		x;

	x = 0;
	while (s[i] != '\0' && x < 2)
	{
		if (s[i] == c)
		{
			i++;
			x++;
		}
		else
		{
			while (s[i] != c && s[x] && z != 1)
				i++;
			x++;
		}
		if (x == z)
			return (i);
	}
	return (i + 1);
}

static int		free_split(char **t, int x)
{
	while (x)
	{
		free(t[x]);
		x--;
	}
	free(t[x]);
	free(t);
	return (0);
}

// da migliorare
char			**split_exp(char const *s, char c)
{
	int		x;
	int		i;
	int		wrd;
	char	**t;

	x = 0;
	i = 0;
	if (!(s))
		return (NULL);
	wrd = count_word(s, c);
	if (!(t = malloc((wrd + 1) * sizeof(char*))))
		return (NULL);
	while (x < wrd)
	{
		if (x == 0)
			i = set_index(s, c, i, 1);
		else
			i = set_index(s, c, i, 2);
		if (!(t[x] = fill_string(s, c, t[x], i)))
			if (!(free_split(t, wrd - 1)))
				return (NULL);
		x++;
	}
	t[x] = NULL;
	return (t);
}