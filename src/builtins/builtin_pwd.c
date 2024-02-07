/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:30:09 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/07 19:35:22 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	builtin_pwd(int argc, char **argv)
{
	char	*current_dir;

	if (argc == 0 || argv == NULL || argv[0] == NULL)
		return (EXIT_FAILURE);
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("minishell pwd error");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(current_dir, STDOUT_FILENO) != ft_strlen(current_dir);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(current_dir);
	return (EXIT_SUCCESS);
}
