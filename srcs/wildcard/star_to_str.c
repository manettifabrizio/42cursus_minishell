/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:30:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/25 16:21:04 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		files_parser(char *path, t_list **head)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	char			*tmp_path;

	if (ft_strcmp(path, "") == 0)
		tmp_path = ft_strjoin(path, "./");
	else
		tmp_path = ft_strdup(path);
	// printf("path = %s\n", tmp_path);
	if (!(dir_stream = opendir(tmp_path)))
	{
		// printf("open error: %s\n", strerror(errno));
		return ;
	}
	while ((dir = readdir(dir_stream)) > 0)
		add_elem_to_list(head, ft_strdup(dir->d_name));
	// print_list_files(*head);
	closedir(dir_stream);
	free(dir);
	free(tmp_path);
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
	// print_list_files(hmatch);
	return (hmatch);
}

t_list		*star_to_str(char *s, char *path, t_list **head)
{
	*head = NULL;
	files_parser(path, head);
	// printf("path = %s\nstr = %s\n", path, s);
	// print_list_files(*head);
	return (find_matches(s, head));
	// path = ft_strjoin_nl(path, t_access_files(l)->name);
}