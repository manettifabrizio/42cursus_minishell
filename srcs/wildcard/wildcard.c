/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:36:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/25 19:55:31 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*cut_str(char *s, int type)
{
	int		i;

	i = (s[0] == '/') ? 1 : 0;
	while (s[i] && s[i] != '/')
		i++;
	if (type == 0)
		return (ft_substr(s, (s[0] == '/') ? 1 : 0, i));
	else if (type == 1)
	{
		i++;
		return (ft_substr(s, i, ft_strlen(s) - i));
	}
	return (s);
}

int			is_dir(char *path, char *fname)
{
	char			*npath;
	struct stat		buf;

	// printf("\npath = %s\nfname = %s\n", path, fname);
	npath = ft_strjoin(path, fname);
	npath = ft_strjoin(npath, "/");
	// printf("frankenpath = %s\n", path);
	stat(npath, &buf);
	free(npath);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void	add_to_final(t_list **hmatch, char *path, t_list **final)
{
	t_list	*l;
	char	*fname;

	l = *hmatch;
	// print_list_files(*hmatch);
	while (l)
	{
		fname = t_access_files(l)->name;
		add_elem_to_list(final, ft_strjoin(path, fname));
		// printf("fname = %s\n", fname);
		l = l->next;
	}
	// print_list_files(*final);
}

void	r_create_list(t_main *m, char *s, char *path, t_list **head, t_list **final)
{
	char	*fname;
	char	*npath;
	t_list	*hmatch;
	t_list	*lmatch;

	// printf("\n\n************************************************\n");
	// printf("s = [%s]\npath = [%s]\n", s, path);
	hmatch = star_to_str(cut_str(s, 0), path, head);
	// printf("====================\n");
	// print_list_files(hmatch);
	// printf("====================\n");
	if (!ft_strchr(s, '/') && hmatch)
		add_to_final(&hmatch, path, final);
	lmatch = hmatch;
	s = cut_str(s, 1);
	while (lmatch)
	{
		fname = t_access_files(lmatch)->name;
		if (is_dir(ft_strdup(path), fname))
		{
			// printf("path = [%s]\n", path);
			npath = ft_strjoin(path, fname);
			npath = ft_strjoin(npath, "/");
			// printf("FINAL = %s\n", final);
			r_create_list(m, s, npath, head, final);
		}
		lmatch = lmatch->next;
	}
	free(s);
	// printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

t_list		*str_to_token_lst(char *str)
{
	t_list	*head;
	int		i;
	char	**tab;

	head = NULL;
	i = 0;
	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	while (tab[i])
	{
		if (!create_tok_lst(tab[i], WORD, &head))
			return (NULL);
		i++;
	}
	return (head);
}

t_list 			*wildcard(t_main *m, char *s)
{
	char		*path;
	t_list		*head;
	t_list		*final;
	t_uint		start;

	if (ft_strncmp(s, "./", 2) == 0)
		path = ft_strdup("./");
	else if (ft_strncmp(s, "/", 1) == 0)
		path = ft_strdup("/");
	else
		path = ft_strdup("");
	final = NULL;
	start = ft_strlen(path);
	// printf("***********************************************\n");
	r_create_list(m, s + start, path, &head, &final);
	// printf("***********************************************\n");
	// print_list_files(head);
	final = list_sort_files(&final);
	return (str_to_token_lst(list_to_str(m, &final)));
}
