/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/09 18:04:53 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

// static size_t	get_str_arr_size(char **lines)
// {
// 	size_t	count;

// 	if (lines == NULL || (*lines) == NULL)
// 		return (0);
// 	count = 0;
// 	while (lines[count])
// 		count++;
// 	return (count);
// }

static int	echo_arg(char *s)
{
	return (printf("%s", s));
}

int	echo(char **argv, t_bool no_newline)
{
	if (argv == NULL || *argv == NULL)
		return (-1);
	while (1)
	{
		echo_arg(*argv);
		argv++;
		if (*argv != NULL)
			printf(" ");
		else
		{
			if (!no_newline)
				printf("\n");
			return (true);
		}
	}
}
