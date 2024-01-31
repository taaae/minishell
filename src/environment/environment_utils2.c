/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:17:51 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 17:37:42 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"

void	extend_environ(void);

int	ft_setenv_defvar(char *name)
{
	char	**env;
	char	*existing_val;

	existing_val = ft_getenv(name);
	if (existing_val != NULL)
		free(existing_val);
	else
	{
		extend_environ();
		env = get_environ();
		while (*env != NULL)
			env++;
		*env = name;
	}
	return (0);
}
