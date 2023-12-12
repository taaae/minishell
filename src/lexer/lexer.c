/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:15:04 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/12 18:45:18 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

t_token	*tokenize(char *line)
{
	t_token	*token_list;
	t_token	*cur_token;

	token_list = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token_list == NULL)
		return (NULL);
	cur_token = token_list;
	while (1)
	{
		get_token(cur_token, line);
		if (cur_token == NULL)
			return (token_list);
	}
	return (NULL);
}
