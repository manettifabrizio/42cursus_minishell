/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:30:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/21 21:32:10 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list		*right_to_star(char *s, int *i, t_list **head)
{
	int		x;
	t_list	*l;
	t_list	*hmatch;
	t_list	*lmatch;

	hmatch = NULL;
	x = *i;
	while (s[x] && s[x] != '*')
		x++;
	l = *head;
	while (l)
	{
		if (ft_strncmp(s + *i, t_access_files(l)->name, x) == 0)
		{
			lmatch = create_files_elem(t_access_files(l)->name);
			if (!hmatch)
				hmatch = lmatch;
			ft_lstadd_back(&hmatch, lmatch);
		}
		l = l->next;
	}
	// free_list(head);
	*i = x;
	if (s[x] == '*')
		return (star(s, i, &hmatch));
	return (hmatch);
}

t_list		*left_to_star(char *s, int i, t_list **head)
{
	int		x;
	char	*tmp;
	t_list	*l;
	t_list	*hmatch;
	t_list	*lmatch;

	x = i;
	hmatch = NULL;
	while (s[x] && s[x] != '*')
		x--;
	tmp = ft_substr(s, x, i - x);
	l = *head;
	while (l)
	{
		if (ft_strncmp(tmp, t_access_files(l)->name, ft_strlen(tmp)) == 0)
		{
			lmatch = create_files_elem(t_access_files(l)->name);
			if (!hmatch)
				hmatch = lmatch;
			ft_lstadd_back(&hmatch, lmatch);
		}
		l = l->next;
	}
	free(tmp);
	//  free_list(head);
	return (hmatch);
}

// t_list		*middle_star(char *s, int i, t_list **head)
// {
// 	head = right_to_star(s, i, head);
// 	head = left_to_star()
// }

t_list		*star(char *s, int *i, t_list **head)
{
	if ((*i) == 0 && !s[((*i)) + 1]) // *
		return (*head);
	else if ((*i) == 0) // *A
		return (right_to_star(s, i, head));
	else if ((*i) == (int)(ft_strlen(s) - 1)) // A*
		return (left_to_star(s, (*i), head));
	else if ((*i) > 0 && (*i) < (int)(ft_strlen(s) - 1)) // A*B
		return (right_to_star(s, i, head));
	return (*head);
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
		if (ft_strcmp(".", dir->d_name) == 0) // tmp
			*head = l;
		ft_lstadd_back(head, l);
	}
	return (head);
}

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

char	*star_to_str(char *s, char *path, t_list **head)
{
	int		i;

	i = 0;
	// s = delete_multiple_stars()
	head = files_parser(path, head);
	print_list_files(head);
	while (s[i])
	{
		if (s[i] == '*')
			*head = star(s, &i, head);
	}
	printf("\n**************************\n");
	print_list_files(head);
	return (s);
}