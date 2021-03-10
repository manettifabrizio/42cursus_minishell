/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:16:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 01:16:29 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_wrd(char *s)
{
	int		x;
	int 	wrd;

	wrd = 0;
	if (s[0] && s[0] != '$') // First word
			wrd++;
	x = -1;
	while (s[++x])
		if (s[x] == '$')
		{
			wrd++;
			x++;
			while (s[x] && (ft_isalpha(s[x]) || s[x] == '?')) // Var characters
				x++;
			if (s[x])
				wrd++;
			else
				break;
		}
	// printf ("wrd = %d\n", wrd);
	return (wrd);
}

static int		is_var(char *s, char **a, int x)
{
	int		start;

	start = x - 1;
	// printf("middle\n");
	while (s[x] && (ft_isalpha(s[x]) || s[x] == '?')) // Because of $?
		x++;
	(*a) = ft_substr(s, start, x - start);
	return (x);
}

static int		is_not_var(char *s, char **a, int x)
{
	int		start;

	start = x;
	// printf("not_var\n");
	while (s[x] && s[x] != '$')
		x++;
	// printf("start = %d x = %d\n", start, x);
	(*a) = ft_substr(s, start, x - start);
	return (x);
}

char		**split_var(char *s)
{
	int		x;
	int		y;
	char	**a;

	x = 0;
	y = 0;
	if (!(a = malloc((count_wrd(s) + 1) * sizeof(char*))))
		return (NULL);
	while (s[x])
	{
		if (s[x] == '$')	// var in the middle
			x = is_var(s, &(a[y]), ++x);
		else					// not a var
			x = is_not_var(s, &(a[y]), x++);
		// printf("a[%d] = %s\n", y, a[y]);
		y++;
		// printf("x = %d\ny = %d\n\n", x, y);
	}
	a[y] = NULL;
	return (a);
}
