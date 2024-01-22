/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:05:42 by trusanov          #+#    #+#             */
/*   Updated: 2024/01/22 14:07:12 by lporoshi         ###   ########.fr       */
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

//rework for DEFVAR
int	builtin_export(int argc, char **argv)
{
	int		res;
	char	**split_res;

	if (argv == NULL || argv[0] == NULL)
		return (FT_ERROR);
	(void)argc;
	res = 0;
	if (argv[1] == NULL)
	{
		ft_putstr_fd("export with no arguments not supported", STDERR_FILENO);
		return (FT_ERROR);
	}
	++argv;
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
