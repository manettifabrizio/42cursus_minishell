/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_nl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:17:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/24 22:47:34 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	*ft_strjoin_nl(char *s, char *s1)
{
	char 	*tmp;

	tmp = ft_strdup(s);
	free(s);
	s = ft_strjoin(tmp, s1);
	free(tmp);
	return (s);
}