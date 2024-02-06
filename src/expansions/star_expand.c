/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:55:50 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 13:31:21 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

char		**get_files_in_cur_dir(void);

static int	match_start_and_end(char *str, char *pattern, char **substrings)
{
	char	*cur_substr;
	int		i;

	cur_substr = substrings[0];
	if (pattern[0] != '*' && ft_strncmp(str, cur_substr,
			ft_strlen(cur_substr)) != 0)
		return (FT_FALSE);
	i = 0;
	while (substrings[i + 1] != NULL)
		i++;
	cur_substr = substrings[i];
	if (pattern[ft_strlen(pattern) - 1] != '*' && ft_strncmp(str
			+ ft_strlen(str) - ft_strlen(cur_substr), cur_substr,
			ft_strlen(cur_substr)) != 0)
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

static char	**compose_expansion_arr(char *pattern, char **candidates)
{
	char	**expansion;
	char	**expansion_orig;
	int		i;
	int		sz;

	i = 0;
	sz = 0;
	while (candidates[i] != NULL)
		if (match_wildcard(candidates[i++], pattern) == FT_TRUE)
			sz++;
	expansion = (char **)ft_calloc(sz + 2, sizeof(char *));
	if (expansion == NULL)
		return (NULL);
	expansion_orig = expansion;
	i = 0;
	while (candidates[i] != NULL)
	{
		if (match_wildcard(candidates[i], pattern) == FT_TRUE)
			*(expansion++) = ft_strdup(candidates[i]);
		i++;
	}
	return (expansion_orig);
}

char	*expand_stars_string(char *pattern)
{
	char	**files;
	char	**expansion;
	char	*result;

	if (!ft_in('*', pattern))
		return (pattern);
	files = get_files_in_cur_dir();
	if (files == NULL)
		return (NULL);
	expansion = compose_expansion_arr(pattern, files);
	if (expansion == NULL)
		return (NULL);
	result = strjoin_str_arr(expansion, ' ');
	if (result[0] == '\0')
		return (pattern);
	free(pattern);
	free_str_arr(&files);
	free_str_arr(&expansion);
	return (result);
}
