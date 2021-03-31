/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:55:11 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/31 13:24:03 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		copy_array(char **dst, char **src, t_uint start)
{
	int	i;

	i = -1;
	while (src[++i])
		if (!(dst[i + start] = ft_strdup(src[i])))
			return ; //error
	dst[i + start] = NULL;
}

static char		**first_line(char *s, t_uint size)
{
	char	**tmp;

	if (!(tmp = malloc((size + 1) * sizeof(char*))))
			return (NULL);
	if (!(tmp[0] = ft_strdup(s)))
			return (NULL);
	// printf("tmp[0] = [%s] = %p\n", tmp[0], tmp[0]);
	tmp[1] = NULL;
	return (tmp);
}

static char		**other_lines(char *s, char **a)
{
	size_t	len;
	char	**tmp;

	len = ft_arrlen_s(a);
	tmp = NULL;
	if (a[0][0])
	{
		if (!(tmp = first_line(s, len + 1)))
			return (NULL);
		copy_array(tmp, a, 1);
	}
	else
	{
		if (!(tmp = malloc((len + 1) * sizeof(char*))))
				return (NULL);
		copy_array(tmp, a, 0);
	}
	return (tmp);
}

char		**add_history(char *s, char **a)
{
	size_t	len;
	char 	**tmp;
	
	len = ft_arrlen_s(a);
	if (!(a[0]))
		tmp = first_line(s, 1);
	else
		tmp = other_lines(s, a);
	ft_free_array(a);
	// printf("a = %p\n", tmp);
	return (tmp);
}

char			**history(char *s, char **a, t_uint hnum)
{
	char	*tmp;

	if (hnum == 0)
	{
		// printf("s = [%s]\n", s);
		if (ft_strcmp(s, "") == 0) //scale array by one
			a = add_history(s, a);
		else
		{
			tmp = ft_strdup(s);
			if (a[1]) // avoid same command repetition
				if (ft_strcmp(s, a[1]) == 0)
					tmp[0] = '\0';
			// printf("a[0] = [%s] = %p\n", a[0], a[0]);	
			free(a[0]);
			if (!(a[0] = ft_strdup(tmp)))
				return (NULL);
			free(tmp);
		}
	}
	// free(s);
	return (a);
}