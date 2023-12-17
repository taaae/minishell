/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:54:57 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 17:00:48 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "builtins.h"

int	builtin_unset(char **argv)
{
	int	res;

	if (argv == NULL)
			return (FT_ERROR);
	res = 0;
	while (*argv)
	{
		if (ft_unsetenv(*argv) == -1)
			res = 1;
		argv++;
	}
	return (res);
}
