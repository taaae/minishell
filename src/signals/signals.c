/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:06 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 17:10:12 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

static int	sig_manager(int sig)
{
	static int	signal = 0;

	if (sig != -1)
		signal = sig;
	return (signal);
}

int	get_sig(void)
{
	return (sig_manager(-1));
}

int	set_sig(int sig)
{
	return (sig_manager(sig));
}

void	parent_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_sig(1);
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	init_parent_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, parent_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
