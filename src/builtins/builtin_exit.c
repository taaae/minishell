/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:33:30 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 17:53:24 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

// if +sigh: all%256
// if -sign: (256 - all%256) % 256
int	get_exit_code(char *s)
{
	long long	tmp;
	int			sign;

	if (s == NULL)
		return (0);
	tmp = 0;
	if (ft_strlen(s) > 19)
		return (-1);
	sign = 0;
	if (*s == '-')
		sign = 1;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
	{
		tmp += *s - '0';
		tmp *= 10;
	}
	if (*s != '\0')
		return (-1);
	if (sign)
		return ((256 - tmp % 256) % 256);
	return (tmp % 256);
}

// If piped, doesn't output anything,
// even though pipe should redirect only stdin
// not stderr. Idk how to fix it for now.
int	builtin_exit(int argc, char **argv)
{
	int	exit_code;

	if (argc > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit_code = get_exit_code(argv[1]);
	if (exit_code == -1)
	{
		perror(argv[1]);
		exit_code = 255;
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(exit_code);
}
