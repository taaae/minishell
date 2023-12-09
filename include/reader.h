/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:48:50 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/09 16:53:27 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/**
 * @brief Initialize the reader before reading lines
 * 
 * @return int 
 */
void	init_reader(void);

/**
 * @brief Clean reader data after we're done with reading
 * 
 * @return int 
 */
void	close_reader(void);

/**
 * @brief Read the line and return it as a string
 * 
 * @return char* 
 */
char	*get_line(void);

#endif