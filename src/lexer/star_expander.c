/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:55:50 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/15 17:26:55 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

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

	if (!ft_in('*', pattern))
		return (FT_ERROR);
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

char	*expand_string(char *pattern)
{
	char	**files;
	char	*expansion;

	files = get_files_in_cur_dir();
	if (files == NULL)
		return (NULL);
	expansion = compose_expansion_str(pattern, files);
	free_str_arr(&files);
	return (expansion);
}

// int main(void) {
//   DIR *d;
//   struct dirent *dir;
//   d = opendir(".");
//   if (d) {
//     while ((dir = readdir(d)) != NULL) {
//       printf("%s\n", dir->d_name);
//     }
//     closedir(d);
//   }
//   return(0);
// }
