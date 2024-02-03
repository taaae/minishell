/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:46:48 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 15:53:13 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

/*
b4 execve:
struct sigaction sa;
    sa.sa_handler = customHandler;
    sa.sa_flags = SA_RESTART;
	tc(s)getattr
*/
//
void	sig_handler_children(int signum)
{
	if (signum == SIGINT)
	{
		return ;
	}
}

void	init_sigs_for_child(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = sig_handler_children;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
