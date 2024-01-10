/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:02:12 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/10 18:06:01 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/**
 * @brief Initialize sinal handlers. Needs to be called before starting
 * the user interaction.
 *
 */
void	init_signal_handlers(void);

/**
 * @brief Get the current stored sighal
 * 
 * @return current signal value
 */
int		get_sig(void);

/**
 * @brief Set the current stored signal.
 * 
 * @param sig 
 * @return signal value after it changed (equals to sig) 
 */
int		set_sig(int sig);

#endif