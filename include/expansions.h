/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:50:32 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/22 14:25:36 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

/**
 * @brief Take a str with * and return str array with all matches in cur. dir.
 * 
 */
char	**expand_star_string(char *pattern);
char	**get_files_in_cur_dir(void);

/**
 * @brief returns a copy of a string, with var names replaced with var vals
 * 
 * Doesn't free() the original string
 * @param str 
 * @return char* 
 */
char	*expand_var_string(char *str);

#endif
