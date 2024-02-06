/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:36:34 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 13:29:46 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "environment.h"
#include "libft.h"

int	update_env_pwd(void)
{
	char	*tmp_pwd;

	if (ft_setenv("OLDPWD", ft_getenv("PWD")) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	tmp_pwd = getcwd(NULL, 0);
	if (tmp_pwd == NULL)
		return (EXIT_FAILURE);
	if (ft_setenv("PWD", tmp_pwd) != EXIT_SUCCESS)
	{
		free(tmp_pwd);
		return (EXIT_FAILURE);
	}
	free(tmp_pwd);
	return (EXIT_SUCCESS);
}

int	builtin_cd(int argc, char **argv)
{
	if (argc < 1 || argv == NULL || argv[0] == NULL)
		return (EXIT_FAILURE);
	if (argc != 2 || argv[1] == NULL || argv[2] != NULL)
	{
		ft_putstr_fd("usage: cd *relative or absolute path*\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(argv[1]) != EXIT_SUCCESS)
	{
		ft_putstr_fd("Problem updating the directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (update_env_pwd() != EXIT_SUCCESS)
	{
		ft_putstr_fd("Problem updating $PWD and $OLDPWD\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
