/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:55:50 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/15 13:56:46 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ordered_substrings_match(char *s, char **substrings)
{
	int	pos;
	int	end;
	int	i;

	pos = 0;
	i = 0;
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

	substrings = ft_split(pattern, '*');
	if (substrings == NULL)
		return (FT_ERROR);
	matched = ordered_substrings_match(str, substrings);
	free_str_arr(&substrings);
	return (matched);
}

static int	append_expansion_str(char **expansion, char *appendix)
{
	char	*temp;

	temp = ft_strjoin(*expansion, appendix);
	free(*expansion);
	*expansion = temp;
	if (*expansion == NULL)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

char	*compose_expansion_str(char *pattern, char **candidates)
{
	char	*expansion;
	char	*temp;
	int		i;

	expansion = ft_strdup("");
	if (expansion == NULL)
		return (NULL);
	i = 0;
	while (candidates[i] != NULL)
	{
		if (match_wildcard(candidates[i], pattern) == FT_TRUE)
		{
			if (append_expansion_str(&expansion, candidates[i]) == FT_ERROR)
				return (NULL);
			if (candidates[i + 1] != NULL)
			{
				if (append_expansion_str(&expansion, " ") == FT_ERROR)
					return (NULL);
			}
		}
		i++;
	}
	return (expansion);
}
