/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:43:08 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/16 13:49:48 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	match_start_and_end(char *str, char *pattern, char **substrings)
{
	char	*cur_substr;
	int		i;

	cur_substr = substrings[0];
	if (pattern[0] != '*' && \
		strncmp(str, cur_substr, ft_strlen(cur_substr)) != 0)
		return (FT_FALSE);
	i = 0;
	while (substrings[i + 1] != NULL)
		i++;
	cur_substr = substrings[i];
	if (pattern[ft_strlen(pattern) - 1] != '*' && \
		strncmp(str + ft_strlen(str) - ft_strlen(cur_substr), \
				cur_substr, ft_strlen(cur_substr)) != 0)
		return (FT_FALSE);
	return (FT_TRUE);
}
