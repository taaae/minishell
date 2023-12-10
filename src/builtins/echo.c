/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/10 15:15:08 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../libft/libft.h"

int	echo(char **argv, bool no_newline_flag)
{
	char	*output_string;

	output_string = strjoin_str_arr(argv, ' ');
	if (output_string == NULL)
		return (FT_ERROR);
	if (ft_putstr_fd(output_string, STDOUT_FILENO) == FT_ERROR)
		return (FT_ERROR);
	if (no_newline_flag == false)
		if (ft_putchar_fd('\n', STDOUT_FILENO) == FT_ERROR)
			return (FT_ERROR);
	return (FT_SUCCESS);
}