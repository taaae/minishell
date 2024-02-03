/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:46:48 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 16:13:34 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

/*
For the main program:
	
b4 execve:
	Set sigint and sigquit to SIG_DFL behavior.
struct sigaction sa;
    sa.sa_handler = customHandler;
    sa.sa_flags = SA_RESTART;
	tc(s)getattr
*/
//

void	init_sigs_child(void)
{
	//tcsetattr(1, TCSAFLUSH, mirror_termios);
	//what does it do?
	//ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//same question
	rl_catch_signals = 0;
	sig_handler_ctrl_c();
	sig_handler_ctrl_bsl();
}

void	sig_handler_ctrl_c(void)
{
	struct sigaction	sa_c_c;

	sa_c_c.sa_handler = SIG_DFL;
	sa_c_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_c_c.sa_mask);
	sigaction(SIGINT, &sa_c_c, NULL);
}

void	sig_handler_ctrl_bsl(void)
{
	struct sigaction	sa_c_bsl;

	sa_c_bsl.sa_handler = SIG_DFL;
	sa_c_bsl.sa_flags = SA_RESTART;
	sigemptyset(&sa_c_bsl.sa_mask);
	sigaction(SIGINT, &sa_c_bsl, NULL);
}
