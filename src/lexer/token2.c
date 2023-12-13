/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:54:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/13 16:22:45 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

/**
 * @brief Get the next tok len object
 * 
 * Cant possibly get ' ' or '\0'!
 * @param line 
 * @return int 
 */
// for "$" if next is not alnum, interpret as "$" // if ? then you know
int	get_next_tok_len(const char *line)
{
	int	i;
	int	state;

	i = 0;
	if (ft_in(line[i], ONE_SYM_WORDS))
		return (1);
	if (ft_in(line[i], TWO_SYM_WORDS))
		return (parse_2_sym_word(line));
	if (line[i] == '\'')
		return (parse_quotes(line));
	if (line[i] == '\"')
		return (parse_dquotes(line));
	if (ft_isalnum(line[i]) || line[i] == '*' || line == '-')
		return (parse_word(line));
	if (line[i] == '$')
		return (parse_var(line));
}

/*
What entities can I encounter?
1. \0 - return 0
2. quotes: "/'
3. parenth : (/)
4. <
5. >
6. |
7. alnum
8. space - after the word
9. 
*/

/*
States:
found 1sym-token - immediate return

inside a word
inside a <</>>


*/