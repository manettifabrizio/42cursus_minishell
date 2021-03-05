/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:44:02 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/04 18:57:32 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int num)
{
	signaln = num;
}

void	config_term(int n, struct termios *base_term)
{
	struct termios new;
	
	// Set non-canonical input
	if (n == 1)
	{
		tcgetattr(STDIN_FILENO, &new);
		// Disable canonic mode, signals and echo for "^C"
		new.c_lflag &= ~(ICANON|ISIG|ECHO);	
  		tcsetattr(STDIN_FILENO, TCSADRAIN, &new); 
	}
	// Set back strandard canoncal input
	else if (n == 0)
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