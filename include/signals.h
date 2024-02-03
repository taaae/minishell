/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:02:12 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 17:04:57 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/**
 * @brief Initialize sinal handlers. Needs to be called before starting
 * the user interaction.
 *
 */
void	init_parent_signals(void);

/**
 * @brief Initialize signals for child. Call inside a fork process,
 * before execve()
 *
 *
*/
void	init_child_signals(void);

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