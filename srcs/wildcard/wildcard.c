/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:36:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/24 00:02:16 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list_files(t_list **head)
{
	t_list	*l;

	l = *head;
	while (l)
	{
		printf("%s\n", t_access_files(l)->name);
		l = l->next;
	}
}

char		*list_to_str(t_main *m, t_list	**head)
{
	t_uint	len;
	t_list	*l;
	char	*s;
	int		i;

	len = 0;
	l = *head;
	// print_list_files(head);
	while (l)
	{
		len += ft_strlen(t_access_files(l)->name) + 1;
		l = l->next;
	}
	printf("len = %d\n", len);
	if (!(s = malloc(len * sizeof(char))))
		malloc_error(m, s, NO_READING);
	i = 0;
	l = *head;
	while (l)
	{
		ft_strcpy(s + i, t_access_files(l)->name);
		i += ft_strlen(t_access_files(l)->name);
		s[i++] = ' ';
		l = l->next;
	}
	s[i - 1] = 0;
	printf("%s\n", s);
	return (s);
}

char		r_create_list(char **a, char *path)
{
	int		i;
	t_list	*head;
	t_list	*l;

	i = -1;
	head = NULL;
	while (a[++i])
	{
		star_to_str(a[i], path, &head);
		l = head;
		while (l)
		{
			path = ft_strjoin_nl(path, t_access_files(l)->name);
			star_to_str(a[i + 1], path, head);
			l = head;
			while (l)
			{
				path = ft_strjoin_nl(path, t_access_files(l)->name));
				star_to_str(a[i + 1], path, head);
			}
		}
}

char		*wildcard(t_main *m, char *s)
{
	int		i;
	char	**a;
	char	*path;
	t_list	*head;
	t_list	*l;

	a = ft_split(s, '/');
	head = NULL;
	while (a[++i])
	{
		

	}
	return (list_to_str(m, &head));
}