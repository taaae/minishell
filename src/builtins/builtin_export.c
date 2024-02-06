/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:05:42 by trusanov          #+#    #+#             */
/*   Updated: 2024/01/24 22:48:31 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"
#include "libft.h"

static void	invalid_identifier_message(char *name)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	print_export(void)
{
	char	**envlist;
	char	**varcontent;

	envlist = get_environ();
	if (envlist == NULL)
		return (EXIT_FAILURE);
	while (*envlist != NULL)
	{
		varcontent = ft_splitone(*envlist, '=');
		if (varcontent == NULL)
			return (EXIT_FAILURE);
		ft_printf("declare -x %s", varcontent[0]);
		if (varcontent[1] != NULL)
			ft_printf("=\"%s\"", varcontent[1]);
		ft_printf("\n");
		envlist++;
		free(varcontent[0]);
		free(varcontent[1]);
		free(varcontent[2]);
		free(varcontent);
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(int argc, char **argv)
{
	int		res;
	char	**split_res;

	if (argv == NULL || argv[0] == NULL)
		return (FT_ERROR);
	(void)argc;
	res = 0;
	if (argv[1] == NULL)
		return (print_export());
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
