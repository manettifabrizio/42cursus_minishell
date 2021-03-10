/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:09:55 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 19:05:35 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	CTRL-D
// 	bash-3.2$ echo "asdafasdfsdf
// 	> bash: unexpected EOF while looking for matching `"'
// 	bash: syntax error: unexpected end of file

char	*multilines(t_main *m, char *s, t_token_type type)
{
	// printf("type = %d\n", type);
	if (type == PIPE)
		return (multi_pipe_and(m, s, "|"));
	if (type == SQUOTE)
		return (multi_quote(m, s, '\''));
	if (type == DQUOTE)
		return (multi_quote(m, s, '\"'));
	return (NULL);
}
