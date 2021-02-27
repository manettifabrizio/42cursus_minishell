/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:55:11 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/27 20:38:20 by fmanetti         ###   ########.fr       */
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
			return NULL; //error
	if (!(tmp[0] = ft_strdup(s)))
			return NULL; //error
	tmp[1] = NULL;
	return (tmp);
}

static char		**add_history(char *s, char **a)
{
	int		len;
	char 	**tmp;
	
	if (!(a[0]))
		tmp = first_line(s, 1);
	else
	{
		len = -1;
		while (a[++len]);
		if (a[0][0]) // Avoid that a line of tmp is "\0"
		{
			tmp = first_line(s, len + 1);
			copy_array(tmp, a, 1);
		}
		else
		{
			tmp = first_line(s, len);
			copy_array(tmp, a, 0);
		}
	}
	ft_free_array(a);
	return (tmp);
}

char			**history(char *s, char **a, t_uint i, t_uint posy)
{
	if (posy == 0)
	{
		if (i == 0) //scale array by one
			a = add_history(s, a);
		else // string is been written
		{
			free(a[0]);
			if (!(a[0] = ft_strdup(s)))
				return (NULL); 
		}
	}
	return (a);
}