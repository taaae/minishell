/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:16:53 by trusanov          #+#    #+#             */
/*   Updated: 2024/02/06 13:30:41 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"
#include "libft.h"

int	builtin_env(int argc, char **argv)
{
	char	**environ;

	(void)argc;
	if (argv == NULL || argv[0] == NULL)
		return (FT_ERROR);
	if (argv[1] != NULL)
	{
		ft_putstr_fd("env with arguments is not supported\n", STDERR_FILENO);
		return (FT_ERROR);
	}
	environ = get_environ();
	while (*environ != NULL)
	{
		if (ft_strchr(*environ, '=') != NULL)
			ft_printf("%s\n", *environ);
		environ++;
	}
	return (0);
}
