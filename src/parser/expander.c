/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:01:19 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/05 14:02:36 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "environment.h"
#include "minishell.h"

// return start (before first var) and moves ptr to first $ occurrence
static char	*eat_start(char **str_ptr)
{
	char	*res;
	int		var_pos;

	if (ft_strchr(*str_ptr, '$') == NULL)
	{
		res = ft_strdup(*str_ptr);
		*str_ptr = NULL;
		return (res);
	}
	var_pos = ft_strchr(*str_ptr, '$') - *str_ptr;
	res = ft_substr(*str_ptr, 0, var_pos);
	(*str_ptr) += var_pos;
	return (res);
}

static int	closest_delim(char *str)
{
	if (ft_strchr(str, '$') == NULL)
		return (ft_strchr(str, ' ') - str);
	if (ft_strchr(str, ' ') == NULL)
		return (ft_strchr(str, '$') - str);
	if (ft_strchr(str, '$') - str < ft_strchr(str, ' ') - str)
		return (ft_strchr(str, '$') - str);
	else
		return (ft_strchr(str, ' ') - str);
}

// return expanded var (or $ if it is just $)
// and moves ptr to next $ occurrence or to the string end or to the next space
static char	*eat_var(char **str_ptr)
{
	char	*var_name;
	char	*res;
	int		var_pos;

	if ((*str_ptr)[1] == '\0' || (*str_ptr)[1] == '$')
	{
		(*str_ptr)++;
		return (ft_strdup("$"));
	}
	if (!ft_strchr(*str_ptr + 1, '$') && !ft_strchr(*str_ptr + 1, ' '))
	{
		var_name = ft_strdup(*str_ptr + 1);
		*str_ptr += ft_strlen(*str_ptr);
	}
	else
	{
		var_pos = closest_delim(*str_ptr + 1) + 1;
		var_name = ft_substr(*str_ptr, 1, var_pos - 1);
		*str_ptr += var_pos;
	}
	res = ft_getenv(var_name);
    if (ft_strcmp(var_name, "?") == 0) {
        res = ft_itoa(g_return_code);
    }
	free(var_name);
	if (res == NULL)
		return (ft_strdup(""));
	return (res);
}

void	expand_vars(char **str_ptr)
{
	char	*str;
	char	*res;
	char	*tmp;

	str = *str_ptr;
	res = eat_start(&str);
	while (str != NULL && *str != '\0')
	{
		tmp = res;
		res = ft_strjoin(res, eat_start(&str));
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, eat_var(&str));
		free(tmp);
	}
	free (*str_ptr);
	*str_ptr = res;
}
