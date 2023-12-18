/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expand_match_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:43:08 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 15:48:29 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static int	match_start_and_end(char *str, char *pattern, char **substrings)
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

int	match_wildcard(char *str, char *pattern)
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

t_list	*expanded_star_to_token(char *s)
{
	t_token	*tok;
	t_list	*tok_entry;

	tok = (t_token *)ft_calloc(1, sizeof(t_token));
	if (tok == NULL)
		return (NULL);
	tok_entry = (t_list *)ft_calloc(1, sizeof(t_list));
	if (tok_entry == NULL)
	{
		free(tok);
		return (NULL);
	}
	tok->token_string = ft_strdup(s);
	tok->token_len = ft_strlen(s);
	tok->type = TOK_EXPANDED_STAR;
	tok_entry->next = NULL;
	tok_entry->content = (void *)tok;
	return (tok_entry);
}
