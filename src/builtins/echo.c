/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:32:34 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/10 14:54:18 by lporoshi         ###   ########.fr       */
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
	if (output_string != NULL)
		ft_putstr_fd(output_string, stdout);
	if (no_newline_flag == false)
		ft_putchar_fd('\n', stdout);
}
