/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:29:11 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/11 10:14:27 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_wrd(char *s)
{
	int		x;
	int 	wrd;

	// CHANGE CHARACTER TO '$'
	x = -1;
	wrd = 0;
	// printf ("s = %s\n", s);
	if (s[0] != '-' && s[0])
			wrd++;
	// printf("len = %d\n", ft_strlen(s));
	while (s[++x])
	{
		if (s[x] == '-')
		{
			wrd++;
			x++;
			// printf ("s[%d] = %c\n", x, s[x]);
			while (ft_isalpha(s[x]) && s[x])
				x++;
			// printf ("s[%d] = %c\n", x, s[x]);
			if (s[x])
				wrd++;
			else
				break;
		}
	}
	//  printf ("wrd = %d\n", wrd);
	return (wrd);
}

static void		case_1(char **s, char **a, int *x, int *y)
{
	char	*tmp;

	(*x)++;
	tmp = (*s);
	while (ft_isalpha((*s)[*x]) && (*s)[*x])
			(*x)++;
	// printf("**** *x = %d\n", *x);
	a[*y] = malloc(((*x) + 1) * sizeof(char));
	a[*y] = ft_substr(*s, 0, *x);
	(*s) = ft_substr(*s, (*x), ft_strlen(*s) - (*x));
	free(tmp);
	(*x) = 0;
	// printf("a[%d] = %s\n", *y, a[*y]);
	(*y)++;
}

static void		case_2(char **s, char **a, int *x, int *y)
{
	char	*tmp;

	tmp = *s;
	a[*y] = malloc((*x + 1) * sizeof(char));
	a[*y] = ft_substr(*s, 0, *x - 1);
	(*s) = ft_substr(*s, *x, ft_strlen(*s) - *x);
	free(*s);
	*x = 0;
	// printf("a[%d] = %s\n", *y, a[*y]);
	(*y)++;
}

static void		case_3(char **s, char **a, int *x, int *y)
{
	char	*tmp;

	while ((*s)[*x] != '-' && (*s)[*x])
			(*x)++;
	// printf("**** *x = %d\n", *x);
	a[*y] = malloc((*x + 1) * sizeof(char));
	a[*y] = ft_substr(*s, 0, *x);
	tmp = *s;
	if (ft_strlen(*s) - *x != 0)
	{
		(*s) = ft_substr(*s, *x, ft_strlen(*s) - *x);
		free(tmp);
	}
	else
		(*s)[0] = '\0';
	(*x) = 0;
	// printf("a[%d] = %s\n", *y, a[*y]);
	(*y)++;
}

char		**ms_split_var(char *s)
{
	int		x;
	int		y;
	char	**a;

	x = 0;
	y = 0;
	a = malloc ((count_wrd(s) + 1) * sizeof(char*));
	while (s[x])
	{
		if (s[0] == '-')
			case_1(&s, a, &x, &y);
		else if (s[x] == '-' && s[x])
			case_2(&s, a, &x, &y);
		else
			case_3(&s, a, &x, &y);
		// printf("x = %d\ny = %d\ns = %s\n\n", x, y, s);
		if (s[x])
			x++;
	}
	a[y] = NULL;
	return (a);
}
