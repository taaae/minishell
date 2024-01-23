/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:40:02 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/23 17:36:02 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "environment.h"

char	*expand_exec_name(char *name);

extern char	**environ;

int	main(void)
{
	char	*s[] = {
		"ls",
		"git",
		"meson",
		"bgirgbwrgwrg",
		"test",
		"~/Documents/",
		"~/Documents/minishell/a.out",
		"/var/tmp/",
		"/home/lporoshi/Documents/minishell/a.out",
		"./a.out",
		NULL
	};
	int	i = 0;
	ft_initenv(environ);
	while(s[i] != NULL)
	{
		ft_printf("[%s\t->\t%s]\n", s[i], expand_exec_name(s[i]));
		i++;
	}
	ft_terminate_env();
}
