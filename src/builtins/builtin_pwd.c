/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:30:09 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/22 11:37:50 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	builtin_pwd(int argc, char **argv)
{
	char	*current_dir;

	(void)argv;
	if (argv == NULL || argv[0] == NULL)
		return (EXIT_FAILURE);
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("minishell pwd error");
		return (EXIT_FAILURE);
	}
	if (ft_putstr_fd(current_dir, STDOUT_FILENO) != ft_strlen(current_dir))
	{
		perror("ft_printf error");
		free(current_dir);
		return (EXIT_FAILURE);
	}
	if (ft_putchar_fd('\n', STDOUT_FILENO) != 1)
	{
		perror("ft_printf error");
		free(current_dir);
		return (EXIT_FAILURE);
	}
	free(current_dir);
	return (EXIT_SUCCESS);
}
