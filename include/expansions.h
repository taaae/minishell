/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:50:32 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/03 20:17:30 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# define VAR_FIRST_CHARS \
		"abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define VAR_CHARS \
		"0123456789abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/**
 * @brief Take a str with * and return str array with all matches in cur. dir.
 * 
 */
char	**s_string(char *pattern);
char	**get_files_in_cur_dir(void);

/**
 * @brief returns a copy of a string, with var names replaced with var vals
 * 
 * Doesn't free() the original string
 * @param str 
 * @return char* 
 */
char	*expand_vars_string(char *str);

char	*expand_stars_string(char *pattern);

#endif
