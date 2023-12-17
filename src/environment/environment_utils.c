/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:43:11 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 15:47:06 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	***st_get_environ_ptr(void)
{
	static char	**environ;

	return (&environ);
}

char	**get_environ(void)
{
	return (*st_get_environ_ptr());
}

// new_environ should never be NULL!
void	set_environ(char **new_environ)
{
	*st_get_environ_ptr() = new_environ;
}

// reallocates environ to a new buffer with extra NULL at the end
void	extend_environ(void)
{
	size_t	environ_size;
	char	**environ;
	char	**new_environ;

	environ = get_environ();
	environ_size = 0;
	while (*environ++)
		environ_size++;
	new_environ = ft_calloc(environ_size + 2, sizeof(char *));
	environ -= (environ_size + 1);
	ft_memmove(new_environ, environ, environ_size * sizeof(char *));
	free(environ);
	set_environ(new_environ);
}
