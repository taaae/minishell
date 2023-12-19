/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:04 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 13:37:42 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config.h"
#include "lexer.h"
#include "libft.h"
#include <stdbool.h>

t_list	*line_to_tokens(char *line)
{
	t_list	*tokens;

	tokens = tokenize(line);
	if (tokens == NULL)
		return (tokens);
	expand_all_stars(&tokens);
	return (tokens);
}
