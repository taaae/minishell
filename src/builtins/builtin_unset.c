/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:54:57 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/19 15:59:38 by lporoshi         ###   ########.fr       */
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

int	builtin_unset(int argc, char **argv)
{
	int	res;

	(void)argc;
	if (argv == NULL || argv[0] == NULL)
		return (FT_ERROR);
	argv++;
	res = 0;
	while (*argv != NULL)
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
