/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:09:55 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 12:28:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	CTRL-D
// 	bash-3.2$ echo "asdafasdfsdf
// 	> bash: unexpected EOF while looking for matching `"'
// 	bash: syntax error: unexpected end of file

char	*multilines(t_main *m, char *s, t_token_type type)
{
	if (type == PIPE)
		return (multi_pipe_and(m, s, "|"));
	// if (type == S_QUOTE)
	// 	return (multilines_quote(m, s, '\''));
	// if (type == D_QUOTE)
	// 	return (multilines_quote(m, s, '\"'));
	return (NULL);
}
