/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:54:57 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 18:29:32 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "builtins.h"

static void	invalid_identifier_message(char *name)
{
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	builtin_unset(char **argv)
{
	int	res;

	if (argv == NULL)
		return (FT_ERROR);
	res = 0;
	while (*argv)
	{
		if (ft_unsetenv(*argv) == -1)
		{
			invalid_identifier_message(*argv);
			res = 1;
		}
		argv++;
	}
	return (res);
}
