/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:55:56 by trusanov          #+#    #+#             */
/*   Updated: 2024/01/10 18:11:17 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "environment.h"

void	set_environ(char **new_environ);
void	extend_environ(void);

void	ft_initenv(char **envp)
{
	size_t	environ_size;
	size_t	index;
	char	**environ;

	environ_size = 0;
	while (*envp++)
		environ_size++;
	environ = ft_calloc(environ_size + 1, sizeof(char *));
	envp -= (environ_size + 1);
	index = 0;
	while (envp[index] != NULL)
	{
		environ[index] = ft_strdup(envp[index]);
		index++;
	}
	set_environ(environ);
}

static char	**__find_env(const char *name)
{
	char	**environ;

	if (name == NULL || name[0] == '\0' || ft_strrchr(name, '=') != NULL)
		return (NULL);
	environ = get_environ();
	while (*environ != NULL)
	{
		if (ft_strncmp(name, *environ, ft_strlen(name)) == 0
			&& (*environ)[ft_strlen(name)] == '=')
			return (environ);
		environ++;
	}
	return (NULL);
}

char	*ft_getenv(const char *name)
{
	char	**env;

	env = __find_env(name);
	if (env == NULL)
		return (NULL);
	return (ft_substr(*env, ft_strlen(name) + 1, INT_MAX));
}

int	ft_setenv(const char *name, const char *val)
{
	char	**env;
	char	*full_name;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL
		|| (!ft_isalpha(name[0]) && name[0] != '_'))
		return (-1);
	if (val == NULL)
		return (0);
	full_name = ft_calloc(ft_strlen(name) + ft_strlen(val) + 2, sizeof(char));
	ft_strncpy(full_name, name, ft_strlen(name) + 1);
	full_name[ft_strlen(name)] = '=';
	ft_strncpy(full_name + ft_strlen(name) + 1, val, ft_strlen(val) + 1);
	env = __find_env(name);
	if (env != NULL)
	{
		free(*env);
		*env = full_name;
		return (0);
	}
	extend_environ();
	env = get_environ();
	while (*env != NULL)
		env++;
	*env = full_name;
	return (0);
}

int	ft_unsetenv(const char *name)
{
	char	**env;

	if (name == NULL || name[0] == '\0' || ft_strrchr(name, '=') != NULL
		|| (!ft_isalpha(name[0]) && name[0] != '_'))
		return (-1);
	env = __find_env(name);
	if (env == NULL)
		return (0);
	free(*env);
	while (env[1] != NULL)
	{
		env[0] = env[1];
		env++;
	}
	env[0] = NULL;
	return (0);
}
