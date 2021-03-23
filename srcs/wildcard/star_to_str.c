/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:30:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/23 00:04:47 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_files(t_list **head)
{
	t_list	*l;

	l = *head;
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

	lmatch = create_files_elem(s);
	if (!(*hmatch))
		*hmatch = lmatch;
	ft_lstadd_back(hmatch, lmatch);
}

t_list	**files_parser(char *path, t_list **head)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_list			*l;

	if (!(dir_stream = opendir(path)))
		return (NULL);
	while ((dir = readdir(dir_stream)) > 0)
	{
		// printf("name = %s\n num = %llu\n", dir->d_name, dir->d_ino);
		l = create_files_elem(dir->d_name);
		if (ft_strcmp(".", dir->d_name) == 0) // soluzione temporanea
			*head = l;
		ft_lstadd_back(head, l);
	}
	return (head);
}

char	*star_to_str(char *s, char *path, t_list **head)
{
	int		i;
	t_list	*l;
	t_list	*hmatch;
	char	*filename;

	i = 0;
	// s = delete_multiple_stars()
	head = files_parser(path, head);
	l = *head;
	hmatch = NULL;
	while (l)
	{
		filename = t_access_files(l)->name;
		if (starcmp(s, filename))
			add_elem_to_list(&hmatch, filename);
		l = l->next;
	}
	*head = hmatch;
	// printf("\n**************************\n");
	print_list_files(head);
	return (s);
}