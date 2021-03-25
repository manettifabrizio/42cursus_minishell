/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:30:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/24 23:03:26 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_list_files(t_list **head)
// {
// 	t_list	*l;

// 	l = *head;
// 	while (l)
// 	{
// 		printf("%s\n", t_access_files(l)->name);
// 		l = l->next;
// 	}
// }

void		files_parser(char *path, t_list **head)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_list			*l;

	if (!(dir_stream = opendir(path)))
		return ;
	while ((dir = readdir(dir_stream)) > 0)
	{
		// printf("name = %s\n num = %llu\n", dir->d_name, dir->d_ino);
		l = create_files_elem(dir->d_name);
		if (!(*head))
			*head = l;
		ft_lstadd_back(head, l);
	}
	// print_list_files(head);
}

t_list		*find_matches(char *s, t_list **head)
{
	t_list	*l;
	t_list	*hmatch;
	char	*fname;

	l = *head;
	hmatch = NULL;
	while (l)
	{
		fname = t_access_files(l)->name;
		// printf("fname = %s\n", fname);
		if (starcmp(s, fname) && fname[0] != '.')
			add_elem_to_list(&hmatch, fname);
		l = l->next;
	}
	free(s);
	// print_list_files(&hmatch);
	return (hmatch);
}

t_list		*star_to_str(char *s, char *path, t_list **head)
{
	*head = NULL;
	files_parser(path, head);
	// printf("path = %s\nstr = %s\n", path, s);
	return (find_matches(s, head));
	// path = ft_strjoin_nl(path, t_access_files(l)->name);
}