/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:36:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 11:53:39 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*cut_str(char *s, int type)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '/')
		i++;
	if (type == 0)
		return (ft_substr(s, 0, i));
	if (type == 1)
	{
		i++;
		char *tmp = ft_substr(s, i, ft_strlen(s) - i);
		free(s);
		return (tmp);
	}
	return (s);
}

int			is_dir(char *path, char *fname)
{
	char			*npath;
	struct stat		buf;

	npath = ft_strjoin_nl(path, fname);
	npath = ft_strjoin_nl(npath, "/");
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
	while (l)
	{
		fname = t_access_files(l)->name;
		add_elem_to_list(final, ft_strjoin(path, fname));
		l = l->next;
	}
}

void	r_create_list(t_main *m, char *s, char *path, t_list **head, t_list **final)
{
	char	*fname;
	char	*npath;
	t_list	*hmatch;
	t_list	*lmatch;

	hmatch = star_to_str(cut_str(s, 0), path, head);
	if (!ft_strchr(s, '/') && hmatch)
		add_to_final(&hmatch, path, final);
	lmatch = hmatch;
	s = cut_str(s, 1);
	while (lmatch && s[0] != 0)
	{
		fname = t_access_files(lmatch)->name;
		if (is_dir(ft_strdup(path), fname))
		{
			npath = ft_strjoin(path, fname);
			npath = ft_strjoin_nl(npath, "/");
			r_create_list(m, ft_strdup(s), npath, head, final);
			free (npath);
		}
		lmatch = lmatch->next;
	}
	ft_lstclear(&hmatch, files_del);
	free(s);
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
	r_create_list(m, s + start, path, &head, &final);
	if (ft_lstsize(final) == 0)
	{
		free(path);
		return (NULL);
	}
	final = list_sort_files(&final);
	free(path);
	return (lst_to_token_lst(final));
}
