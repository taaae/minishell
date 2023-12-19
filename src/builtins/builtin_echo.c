/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 15:36:00 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

int	builtin_echo(char **argv)
{
	char	*output_string;
	bool	no_newline;

	if (argv == NULL || argv[0] == NULL)
		return (FT_SUCCESS);
	no_newline = !ft_strcmp(argv[0], "-n");
	argv += (int)(no_newline);
	output_string = strjoin_str_arr(argv, ' ');
	if (output_string == NULL)
		return (FT_ERROR);
	if (ft_putstr_fd(output_string, STDOUT_FILENO) == FT_ERROR)
	{
		free(output_string);
		return (FT_ERROR);
	}
	if (no_newline == false)
	{
		if (ft_putchar_fd('\n', STDOUT_FILENO) == FT_ERROR)
		{
			free(output_string);
			return (FT_ERROR);
		}
	}
	free(output_string);
	return (FT_SUCCESS);
}
