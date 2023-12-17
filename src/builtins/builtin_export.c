/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:05:42 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 17:29:39 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "builtins.h"

// todo change it so ft_setenv checks whether name is valid identifier and also add error output for builtin_unset and builtin_export
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
		if (ft_strrchr(*argv, '=') == NULL)
		{
			if (*argv[0] == '\0')
				res = 1;
			argv++;
			continue ;
		}
		split_res = ft_splitone(*argv, '=');
		if (ft_setenv(split_res[0], split_res[1]) == -1)
			res = 1;
		free_str_arr(&split_res);
		argv++;
	}
	return (res);
}
