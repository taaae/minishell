/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander_match_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:43:08 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 13:33:47 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	match_start_and_end(char *str, char *pattern, char **substrings)
{
	char	*cur_substr;
	int		i;

	cur_substr = substrings[0];
	if (pattern[0] != '*' && \
		ft_strncmp(str, cur_substr, ft_strlen(cur_substr)) != 0)
		return (FT_FALSE);
	i = 0;
	while (substrings[i + 1] != NULL)
		i++;
	cur_substr = substrings[i];
	if (pattern[ft_strlen(pattern) - 1] != '*' && \
		ft_strncmp(str + ft_strlen(str) - ft_strlen(cur_substr), \
				cur_substr, ft_strlen(cur_substr)) != 0)
		return (FT_FALSE);
	return (FT_TRUE);
}

static int	ordered_substrings_match(char *s, char **substrings)
{
	int	pos;
	int	end;
	int	i;

	pos = 0;
	i = 0;
	if (ft_in('\"', s) && ft_in('\'', s))
		return (FT_FALSE);
	end = ft_strlen(s);
	while (substrings[i] != NULL)
	{
		if (ft_strnstr(s + pos, substrings[i], end - pos) == NULL)
			return (FT_FALSE);
		pos += ft_strlen(substrings[i]);
		i++;
	}
	if (pos == 0)
		return (FT_FALSE);
	return (FT_TRUE);
}

static int	match_wildcard(char *str, char *pattern)
{
	char	**substrings;
	int		matched;

	if (str[0] == '.')
		return (FT_FALSE);
	if (!ft_in('*', pattern))
		return (FT_ERROR);
	substrings = ft_split(pattern, '*');
	if (substrings == NULL)
		return (FT_ERROR);
	if (substrings[0] == NULL)
		return (FT_TRUE);
	if (match_start_and_end(str, pattern, substrings) == FT_FALSE)
		return (FT_FALSE);
	matched = ordered_substrings_match(str, substrings);
	free_str_arr(&substrings);
	return (matched);
}

static int	append_expansion_str(char **expansion, char *appendix)
{
	char	*temp;

	if (ft_in('\'', appendix))
		appendix = ft_str_surround(&appendix, '\"');
	else if (ft_in('\"', appendix))
		appendix = ft_str_surround(&appendix, '\'');
	if (appendix == NULL)
		return (FT_ERROR);
	temp = ft_strjoin(*expansion, appendix);
	free(*expansion);
	*expansion = temp;
	if (*expansion == NULL)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
