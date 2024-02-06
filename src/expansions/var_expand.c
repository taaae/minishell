/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:47:25 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 13:35:05 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "expansions.h"
#include "environment.h"

/**
 * @brief Takes a ptr to a string with a varname (with $ sign), expands it,
 * frees the prev memory.
 * 
 * If varname is incorrect, empty string is the result
 * @param str 
 * @return int 
 */
int	expand_var_string(char **str)
{
	char	*val;

	if (str == NULL || *str == NULL)
		return (FT_ERROR);
	val = ft_getenv((*str) + 1);
	if (val == NULL)
		val = ft_strdup("");
	if (val == NULL)
		return (FT_ERROR);
	free(*str);
	*str = val;
	return (FT_SUCCESS);
}

/**
 * @brief Takes strarr, expands all strs in it that are varnames
 * 
 * @param split_str 
 * @return int 
 */
int	expand_all_vars(char ***split_str)
{
	char	**str_arr;

	str_arr = *split_str;
	while (*str_arr != NULL)
	{
		if ((*str_arr)[0] == '$' && expand_var_string(str_arr) != FT_SUCCESS)
		{
			free_str_arr(split_str);
			return (FT_ERROR);
		}
		str_arr++;
	}
	return (FT_SUCCESS);
}

/**
 * @brief tells how many ptrs allocate for var split
 * 
 * @param str 
 * @return int 
 */
int	count_var_split_sz(char *str)
{
	int		i;
	int		count;
	bool	in_var;

	i = 0;
	count = 0;
	in_var = str[i] == '$';
	while (str[i])
	{
		if (in_var && !ft_in(str[i], VAR_CHARS))
		{
			in_var = false;
			count += 1;
		}
		if (!in_var && str[i] == '$' && ft_in(str[i + 1], VAR_FIRST_CHARS))
		{
			in_var = true;
			++count;
			++i;
		}
		++i;
	}
	return (count);
}

/**
 * @brief takes str, and splits it to 2 types of substrings
 * either smth between the varname and ^$, or the varname
 * 
 * returns string array
 * @param str 
 * @return char** 
 */
char	**split_var_string(char *str)
{
	char	**res;
	int		sz;

	sz = count_var_split_sz(str);
	res = (char **)ft_calloc(sz + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (sz)
	{
		return (NULL);
	}
	return (NULL);
}

/**
 * @brief Return str with all vars expanded, don't free the original string.
 * 
 * @param str 
 * @return char* 
 */
char	*expand_vars_string(char *str)
{
	char	**split_str;
	char	*result;

	split_str = split_var_string(str);
	if (split_str == NULL)
		return (NULL);
	if (expand_all_vars(&split_str) == FT_ERROR)
		return (NULL);
	result = str_arr_cat(split_str);
	free_str_arr(&split_str);
	return (result);
}
