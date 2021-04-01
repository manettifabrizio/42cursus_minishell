/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:16:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/01 10:56:37 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_wrd(char *s)
{
	int		x;
	int 	wrd;

	x = 0;
	wrd = 0;
	while (s[x])
		if (s[x] == '$')
		{
			if (x == 0 || (x > 0 && s[x - 1] != '\\'))
				wrd++;
			x++;
			while (s[x] && (ft_isalpha(s[x]) || s[x] == '?'))
				x++;
		}
		else
		{
			wrd++;
			while (s[x] && !(s[x] == '$' && (x == 0 ||
				(x > 0 && s[x - 1] != '\\'))))
				x++;
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
	while (s[x])
	{
		if ((s[x] == '$' && (x == 0 || (x > 0 && s[x - 1] != '\\'))))
			break ;
		// printf("s[x] = %c\n", s[x]);	
		x++;
	}
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
	// printf("s = %s\n", s);
	while (s[x])
	{
		// printf("s[x] = %c\n", s[x]);
		if (s[x] == '$' && (x == 0 || s[x - 1] != '\\'))
			x = is_var(s, &(a[y]), ++x);
		else
			x = is_not_var(s, &(a[y]), x++);
		// printf("a[%d] = %s\n", y, a[y]);
		y++;
		// printf("x = %d\ny = %d\n\n", x, y);
	}
	a[y] = NULL;
	// ft_print_array(a, "a");
	return (a);
}
