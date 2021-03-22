/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:36:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/19 17:10:11 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*stars_to_path(char *s, char *path)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	
	if (!(dir_stream = opendir(path)))
			return (NULL);
		while ((dir = readdir(dir_stream)) > 0)
		{
			
		}
}

char	*asterisk_parser(char *s)
{
	int		i;
	int		start;
	char	*path;

	i = -1;
	start = 0;
	path = ft_strdup("./");
	while (s[++i])
	{
		if (s[i] == '/')
		{	
			stars_to_path(ft_substr(s, start, i - start), path);
	}
}

int		wildcard(t_main *m, char *s)
{
	

}