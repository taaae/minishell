/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:05:42 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 18:29:12 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "builtins.h"

static void	invalid_identifier_message(char *name)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	builtin_export(char **argv)
{
	int		res;
	char	**split_res;

	res = 0;
	if (argv == NULL)
		return (FT_ERROR);
	if (argv[0] == NULL)
	{
		ft_putstr_fd("export with no arguments not supported", STDERR_FILENO);
		return (FT_ERROR);
	}
	while (*argv)
	{
		split_res = ft_splitone(*argv, '=');
		if (ft_setenv(split_res[0], split_res[1]) == -1)
		{
			invalid_identifier_message(*argv);
			res = 1;
		}
		free_str_arr(&split_res);
		argv++;
	}
	return (res);
}
