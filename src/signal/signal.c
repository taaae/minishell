/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:06 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/07 12:41:50 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

static int	sig_storage(int sig)
{
	static int	signal = -1;

	if (sig != -1)
		signal = sig;
	return (signal);
}

int	get_sig(void)
{
	return (sig_storage(-1));
}

int	set_sig(int sig)
{
	return (sig_storage(sig));
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_sig(SIGINT);
		rl_redisplay();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	init_signal_handlers(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
