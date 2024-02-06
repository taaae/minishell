/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/22 12:25:34 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static int	echo_printer(char *s, bool no_nl)
{
	if (s == NULL)
		return (EXIT_FAILURE);
	if (ft_putstr_fd(s, STDOUT_FILENO) != ft_strlen(s))
	{
		free(s);
		return (EXIT_FAILURE);
	}
	if (no_nl == false)
	{
		if (ft_putchar_fd('\n', STDOUT_FILENO) != 1)
		{
			free(s);
			return (EXIT_FAILURE);
		}
	}
	free(s);
	return (EXIT_SUCCESS);
}

int	builtin_echo(int argc, char **argv)
{
	char	*output_string;
	bool	no_newline;

	if (argc < 1 || argv == NULL || argv[0] == NULL)
		return (EXIT_FAILURE);
	no_newline = false;
	if (argv[1] != NULL && !ft_strcmp(argv[1], "-n"))
	{
		no_newline = true;
		argv++;
	}
	output_string = strjoin_str_arr(argv + 1, ' ');
	return (echo_printer(output_string, no_newline));
}
