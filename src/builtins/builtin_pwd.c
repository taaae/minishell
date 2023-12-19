/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:30:09 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 15:59:44 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	builtin_pwd(int argc, char **argv)
{
	char	*current_dir;

	(void)argv;
	if (argv == NULL || argv[0] == NULL)
		return (FT_ERROR);
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		return (FT_ERROR);
	if (ft_putstr_fd(current_dir, STDOUT_FILENO) == FT_ERROR)
	{
		free(current_dir);
		return (FT_ERROR);
	}
	if (ft_putchar_fd('\n', STDOUT_FILENO) == FT_ERROR)
	{
		free(current_dir);
		return (FT_ERROR);
	}
	free(current_dir);
	return (FT_SUCCESS);
}
