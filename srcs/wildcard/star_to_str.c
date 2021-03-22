/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:30:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/22 14:58:25 by fmanetti         ###   ########.fr       */
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

// t_list		*right_to_star(char *s, int *i, t_list **head)
// {
// 	int		x;
// 	char	*tmp;
// 	char	*filename;
// 	t_list	*l;
// 	t_list	*hmatch;
// 	t_list	*lmatch;

// 	printf("---- RIGTH ----\n");
// 	hmatch = NULL;
// 	x = *i;
// 	printf("x = %d\n", x);
// 	while (s[x] && s[x] != '*')
// 		x++;
// 	printf("s[%d] = %c\n", x, s[x]);
// 	tmp = ft_substr(s, *i, x - *i);
// 	printf("tmp = %s\n", tmp);
// 	l = *head;
// 	while (l)
// 	{
// 		char *s1;
// 		filename = t_access_files(l)->name;
// 		if ((s1 = ft_strstr(filename, tmp)))
// 		{
// 			if (s[x] == '*')
// 				add_elem_to_list(&hmatch, lmatch, filename);
// 			else if (s1[x - *i] == 0)
// 				add_elem_to_list(&hmatch, lmatch, filename);
// 			// printf("s1 = %s s1[x - *i] = %c\n", s1, s1[x - *i]);
// 		}
// 		l = l->next;
// 	}
// 	free(tmp);
// 	// free_list(head);
// 	print_list_files(&hmatch);
// 	*i = x;
// 	if (s[x] == '*')
// 		return (star(s, i, &hmatch));
// 	return (hmatch);
// }

// t_list		*left_to_star(char *s, int i, t_list **head)
// {
// 	int		x;
// 	char	*tmp;
// 	char 	*s1;
// 	char	*filename;
// 	t_list	*l;
// 	t_list	*hmatch;
// 	t_list	*lmatch;

// 	x = i;
// 	printf("---- LEFT ----\n");
// 	hmatch = NULL;
// 	printf("s[%d] = %c\n", x, s[x]);
// 	x--;
// 	while (x > 0 && s[x] != '*')
// 		x--;
// 	printf("s[%d] = %c\n", x, s[x]);
// 	printf("x = %d i = %d\n", x, i);
// 	tmp = ft_substr(s, x, (i - x));
// 	printf("tmp = %s\n", tmp);
// 	// print_list_files(head);
// 	l = *head;
// 	while (l)
// 	{
// 		filename = t_access_files(l)->name;
// 		if ((s1 = ft_strstr(filename, tmp)))
// 		{
// 			if (s[x] == '*')
// 				add_elem_to_list(&hmatch, lmatch, filename);
// 			else if (ft_strncmp(s, tmp, i - x))
// 				add_elem_to_list(&hmatch, lmatch, filename);
// 		}
// 		l = l->next;
// 	}
// 	free(tmp);
// 	//  free_list(head);
// 	print_list_files(&hmatch);
// 	return (hmatch);
// }

// t_list		*middle_star(char *s, int *i, t_list **head)
// {
// 	*head = left_to_star(s, (*i), head);
// 	(*i)++;
// 	*head = right_to_star(s, i, head);
// 	return (*head);
// }

// t_list		*star(char *s, int *i, t_list **head)
// {
// 	t_list	*l;
// 	t_list	*hmatch;
// 	char	*filename;
	
// 	l = *head;
// 	hmatch = NULL;
// 	while (l)
// 	{
// 		filename = t_access_files(l)->name;
// 		if (starcmp(*s, filename))
// 			add_elem_to_list(hmatch, s);
// 	}
// 	return (*head);
// }

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
	printf("\n**************************\n");
	print_list_files(head);
	return (s);
}