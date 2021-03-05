/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:16:41 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/05 11:19:20 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

#define		CURSOR_LEFT		"\033[D"
#define		CURSOR_RIGHT	"\033[C"
#define		CLEAR_LINE		"\033[0K"

#define		SEPARATOR		31
#define		D_QUOTE			34
#define		S_QUOTE			39

#define		CTRL_C			3
#define		CTRL_D			4
#define		CTRL_Z			26
#define		ESCAPE			27
#define		CTRL_BSLASH		28
#define		DELETE			51
#define		ARR_UP			65
#define		ARR_DOWN		66
#define		ARR_RIGHT		67
#define		ARR_LEFT		68
#define		END				70
#define		HOME			72
#define		BACKSPACE		127

#define		ERRNO			0
#define		NO_ERRNO		1
#define		ERROR			"\033[0;31merror\033[0m"

#endif