/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 15:53:10 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

static int	echo_printer(char *s, bool no_nl)
{
	if (s == NULL)
		return (FT_ERROR);
	if (ft_putstr_fd(s, STDOUT_FILENO) == FT_ERROR)
	{
		free(s);
		return (FT_ERROR);
	}
	if (no_nl == false)
	{
		if (ft_putchar_fd('\n', STDOUT_FILENO) == FT_ERROR)
		{
			free(s);
			return (FT_ERROR);
		}
	}
	free(s);
	return (FT_SUCCESS);
}

int	builtin_echo(int argc, char **argv)
{
	char	*output_string;
	bool	no_newline;

	(void)argc;
	if (argv == NULL || argv[0] == NULL)
		return (FT_SUCCESS);
	no_newline = false;
	if (argv[1] != NULL && !ft_strcmp(argv[1], "-n"))
	{
		no_newline = true;
		argv++;
	}
	output_string = strjoin_str_arr(argv + 1, ' ');
	return (echo_printer(output_string, no_newline));
}
