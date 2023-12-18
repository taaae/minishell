/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:16:53 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 16:55:07 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "builtins.h"

int	builtin_env(char **argv)
{
	char	**environ;

	if (argv == NULL)
		return (FT_ERROR);
	if (argv[0] != NULL)
	{
		ft_putstr_fd("env with arguments is not supported", STDERR_FILENO);
		return (FT_ERROR);
	}
	environ = get_environ();
	while (*environ != NULL)
	{
		ft_printf("%s\n", *environ);
		environ++;
	}
	return (0);
}
