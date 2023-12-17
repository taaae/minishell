/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:30:09 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/15 14:02:50 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	builtin_pwd(void)
{
	char	*current_dir;

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
