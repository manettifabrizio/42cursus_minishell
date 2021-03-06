/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:12:43 by viroques          #+#    #+#             */
/*   Updated: 2021/03/06 13:10:52 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        **get_directories_path(char **env)
{
    int i;
    char **directories;

    i = 0;
    while (env[i])
    {
        if ((ft_strnstr(env[i], "PATH", 4)))
        {
            directories = ft_split(env[i] + 5, ':');
            return (directories);
        }
        i++;
    }
    return (NULL);
}

char    *search_path(char *cmd_name, char **pathdirs)
{
    DIR             *dir_stream;
    struct dirent   *dir; 
    char            *path;
    int             i;
    
    i = 0;
    while (pathdirs[i])
    {
        if (!(dir_stream = opendir(pathdirs[i])))
            return (NULL);
        while ((dir = readdir(dir_stream)) > 0)
        {
            if (ft_strncmp(dir->d_name, cmd_name, ft_strlen(dir->d_name)) == 0)
            {
                path = ft_strjoin(pathdirs[i], cmd_name);
                closedir(dir_stream);
                return (path);
            }
        }
        i++;
        closedir(dir_stream);
    }
    return (NULL);
}