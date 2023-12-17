/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:44:11 by trusanov          #+#    #+#             */
/*   Updated: 2023/12/17 17:07:22 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

/**
 * @brief Copies envp into dinamically allocated array.
 * This functions should always be called before using
 * ft_getenv ft_setenv ft_unsetenv.
 * @warning should be called only one time to avoid memory leaks
 */
void	ft_initenv(char **envp);

/**
 * @brief Returns NULL-terminated array of environment variables.
 * Used for passing it into functions such as execve() and for builtin_env
 */
char	**get_environ(void);

/**
 * @brief The ft_getenv() function obtains the current value of the environment
 * variable, name.
 * @return value of the variable. Dinamically allocated
 * and should be freed manually. NULL if not found.
 * @warning ft_initenv should be called before using this function
*/
char	*ft_getenv(const char *name);

/**
 * @brief The ft_setenv() function inserts or resets the environment variable
 * name in the current environment list. If the variable name does not exist
 * in the list, it is inserted with the given value.
 * If the variable does exist, it is reset to the given value.
 * @return  0 if successful; -1 if name is invalid
 * @warning ft_initenv should be called before using this function
 */
int		ft_setenv(const char *name, const char *val);

/**
 * @brief The unsetenv() function deletes an instance of the variable name
 * pointed to by name from the list.
 * @note Only the variable name should be given; "NAME=value" will not work.
 * @return 0 if successful; -1 if name is invalid
 * @warning ft_initenv should be called before using this function
 */
int		ft_unsetenv(const char *name);

#endif
