/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:30:09 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/10 17:47:54 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	pwd(char **argv)
{
	char	*current_dir;

	if (argv == NULL)
		return (FT_ERROR);
	if (*argv != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDOUT_FILENO);
		return (1);
	}
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		return (FT_ERROR);
	ft_putstr_fd(current_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(current_dir);
	return (FT_SUCCESS);
}
