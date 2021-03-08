/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:26:01 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/07 17:37:39 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <unistd.h>
# include <stdio.h>

typedef unsigned int	t_uint;

// typedef	struct		s_tree
// {
// 	char			*w1;
// 	char			*w2;
// }					t_tree;

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_cursor
{
	t_uint	x;
	t_uint	y;
}					t_cursor;

typedef	struct		s_main
{
	char			**env;
	char			*home;
	t_env			*ehead;
	t_cursor		*pos;
	char			**hist;
	char			*hist_path;
	int				exit_status;
	// commands
	char			**arr;
	// path variable
	char			**pathdirs;
	//multilines
	t_uint			multilns;
	struct termios	*base_term;
}					t_main;

#endif