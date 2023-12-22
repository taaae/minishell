/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:47:25 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/22 14:29:34 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_var_string(char *str)
{
	char	**split_str;

	
}

/**
 * @brief Return str with all vars expanded, don't free the original string.
 * 
 * @param str 
 * @return char* 
 */
char	*expand_var_string(char *str)
{
	char	**split_str;
	char	*result;

	split_str = split_var_string(str);
	if (split_str == NULL)
		return (NULL);
	expand_all_vard(&split_str);
	if (split_str == NULL)
		return (NULL);
	result = str_arr_cat(split_str);
	free(split_str);
	return (result);
}
