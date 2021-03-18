/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:44:02 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/18 14:52:19 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int signalnum)
{
	if (signalnum == SIGINT)
		ft_putstr("\b\b  \b\b");
	if (signalnum == SIGQUIT)
		ft_putstr("Quit: 3\n");
}

void	set_term_noncano()
{
	struct termios new;
	
	// Set non-canonical input
	tcgetattr(STDIN_FILENO, &new);
	// Disable canonic mode, signals and echo for "^C"
	new.c_lflag &= ~(ICANON|ISIG|ECHO);	
	tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
}

void	set_term_cano(struct termios *base_term)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, base_term);
}

// c_lflag
// ISIG   When any of the characters INTR, QUIT, SUSP, or DSUSP are
//               received, generate the corresponding signal.
// NOFLSH Disable flushing the input and output queues when
//               generating signals for the INT, QUIT, and SUSP characters.

// c_cc
// VINTR  (003, ETX, Ctrl-C, or also 0177, DEL, rubout) Interrupt
//               character (INTR).  Send a SIGINT signal.  Recognized when
//               ISIG is set, and then not passed as input.
// VQUIT  (034, FS, Ctrl-\) Quit character (QUIT).  Send SIGQUIT
//               signal.  Recognized when ISIG is set, and then not passed
//               as input.
// VSUSP  (032, SUB, Ctrl-Z) Suspend character (SUSP).  Send SIGTSTP
//               signal.  Recognized when ISIG is set, and then not passed
//               as input.