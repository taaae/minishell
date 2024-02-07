/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:46:48 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/07 19:29:56 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_sigint_child(int sig)
{
	(void)sig;
	exit(130);
}

void	handle_sigquit_child(int sig)
{
	(void)sig;
	exit(131);
}

void	init_child_signals(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigquit_child);
}
