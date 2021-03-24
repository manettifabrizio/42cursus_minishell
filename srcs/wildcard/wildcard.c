/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:36:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/24 16:43:33 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list_files(t_list *head)
{
	t_list	*l;

	l = head;
	while (l)
	{
		printf("%s\n", t_access_files(l)->name);
		l = l->next;
	}
}

char		*list_to_str(t_main *m, char *path, t_list **head)
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
		len += ft_strlen(path);
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
		ft_strcpy(s + i, path);
		i += ft_strlen(path);
		ft_strcpy(s + i, t_access_files(l)->name);
		i += ft_strlen(t_access_files(l)->name);
		s[i++] = ' ';
		l = l->next;
	}
	s[i - 1] = 0;
	// printf("%s\n", s);
	return (s);
}

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

int			is_dir(char *path, char *filename)
{
	char			*npath;
	struct stat		buf;

	// printf("path = %s\nfilename = %s\n", path, filename);
	npath = ft_strjoin(path, filename);
	npath = ft_strjoin(npath, "/");
	// printf("frankenpath = %s\n", path);
	stat(npath, &buf);
	free(npath);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

char	*r_create_list(t_main *m, char *s, char *path, t_list **head, char *final)
{
	char	*fname;
	char	*npath;
	t_list	*hmatch;
	t_list	*lmatch;

	// printf("---------------\n");
	// printf("s = [%s]\npath = [%s]\n", s, path);
	hmatch = star_to_str(cut_str(s, 0), path, head);
	// printf("====================\n");
	// print_list_files(hmatch);
	// printf("====================\n");
	if (!ft_strchr(s, '/') && hmatch)
		final = ft_strjoin(final, list_to_str(m, path, &hmatch));
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
			r_create_list(m, s, npath, head, final);
		}
		lmatch = lmatch->next;
	}
	free(s);
	return (final);
}

char		*wildcard(t_main *m, char *s)
{
	int		i;
	char	*path;
	t_list	*head;
	char	*final;

	path = ft_strdup("./");
	final = ft_strdup("");
	// star_to_str(s, path, &head);
	// printf("***********************************************\n");
	printf("%s\n", r_create_list(m, s, path, &head, final));
	// printf("***********************************************\n");
	// print_list_files(head);
	// return (list_to_str(m, &head));
	return (NULL);
}