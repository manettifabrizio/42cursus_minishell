/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 23:03:10 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/25 09:41:24 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_list_files(t_list *head)
{
	t_list	*l;

	l = head;
	while (l)
	{
		printf("%s\n", t_access_files(l)->name);
		l = l->next;
	}
}

t_list		*create_files_elem(char *s)
{
	t_files	*l;
	t_list	*tmp;

	if (!(l = malloc(sizeof(t_files))))
		return (0);
	l->name = s;
	if (!(tmp = ft_lstnew(l)))
		return (0);
	return (tmp);
}

void		add_elem_to_list(t_list **hmatch, char *s)
{
	t_list	*lmatch;

	// printf("fname = %s\n", s);
	lmatch = create_files_elem(s);
	// if (!(*hmatch))
	// 	*hmatch = lmatch;
	// printf("hmatch = %p\n", *hmatch);
	ft_lstadd_back(hmatch, lmatch);
}

char		*list_to_str(t_main *m, t_list **head)
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
	// printf("len = %d\n", len);
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
	// printf("%s\n", s);
	return (s);
}