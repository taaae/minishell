/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/10 15:05:06 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "builtins.h"
#include "../../libft/libft.h"

int	echo(char **argv, bool no_newline_flag)
{
	char	*output_string;

	output_string = strjoin_str_arr(argv, ' ');
	if (output_string == NULL)
		return (FT_ERROR);
	if (ft_putstr_fd(output_string, stdout) == FT_ERROR)
		return (FT_ERROR);
	if (no_newline_flag == false)
		if (ft_putchar_fd('\n', stdout) == FT_ERROR)
			return (FT_ERROR);
	return (FT_SUCCESS);
}
