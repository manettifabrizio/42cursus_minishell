/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:44:38 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/05 19:44:21 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main()
{
	char a, b, c;

	scanf("%c%c%c\n", &a, &b, &c);
	// for(int i = 0; s[i]; i++)
	printf("s[%d] = %d | %c\n", 0, a, a);
	printf("s[%d] = %d | %c\n", 1, b, b);
	printf("s[%d] = %d | %c\n", 2, c, c);
	return (0);
}