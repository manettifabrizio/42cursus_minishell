/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:41 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/11 10:40:22 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		sub_vars(char **s, t_env *head)
{
	t_env	*l;
	char 	*tmp;

	l = head;
	while (l)
	{
		// printf("---------------\n");
		if (ft_strcmp(l->name, head->name) == 0)
		{
			tmp = (*s);
			tmp++;
		}
		if (ft_strcmp(tmp, l->name) == 0)
		{
			// printf("0000000000\n");
			// printf("%s\n", (*s));
			tmp = (*s);
			(*s) = ft_strdup(l->value);
			free(tmp);
			return ;
		}
		l = l->next;
	}
	(*s)[0] = '\0';
}

static char		*create_string(char **a)
{
	int		x;
	int 	y;
	int		z;
	char	*s;

	x = -1;
	z = 0;
	// ft_print_array(a);
	if (!(a[0]))
		return (NULL);
	while (a[++x])
	{
		y = -1;
		while (a[x][++y])
			z++;
	}
	if (!(s = malloc((z + 1) * sizeof(char))))
		return (NULL);
	x = -1;
	z = -1;
	while (a[++x])
	{
		y = -1;
		while (a[x][++y])
			s[++z] = a[x][y];
	}
	s[++z] = '\0';
	return (s);
}

static char		*check_vars(char *s, t_env *head)
{
	int		x;
	char	*tmp;
	char 	**a;
	t_env	*l;
	
	x = -1;
	a = ms_split_var(s);
	// ft_print_array(a);
	l = head;
	if (a[0] != NULL)
	{
		while (a[++x])
		{
			// printf("a[%d] = %s\n", x, a[x]);
			if (a[x][0] == '-')
				sub_vars(&(a[x]), head);
		}
	}
	return (create_string(a));
}

// Non funziona con le "" ma teoricamente l'array dovrebbe arrivare senza

int				ft_echo(char **a, t_env *head)
{
	int x;

	x = 0;
	if (!(a[1]))
		printf("\n");
	else
		if (ft_strcmp(a[1], "-n") == 0)
		{
			x++;
			if (a[2])
				while (a[++x])
				{
					ft_putstr(check_vars(a[x], head));
					if (a[x + 1])
						ft_putchar(' ');
				}
		}
		else
		{
			while (a[++x])
			{
				ft_putstr(check_vars(a[x], head));
				if (a[x + 1])
					ft_putchar(' ');
			}
			printf ("\n");
		}
	return (1);
}