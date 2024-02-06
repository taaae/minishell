/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:41:16 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 19:56:37 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FIND_H
# define EXEC_FIND_H

typedef enum e_exec_status
{
	FT_EXECNAME_OK = 0,
	FT_EXECNAME_NOEXEC = 1,
	FT_EXECNAME_NOFILE = 2
}	t_exec_status;

/**
 * @brief Takes exec name from shell and expands it to full path+name of exec
 * 
 * Searches $PATH, handles relative path, absolute path, ~/...
 * Does not free "name"'s memory
 * Ensures that the file exists and is executable
 * Otherwise returns NULL
 * @param name 
 * @return char* 
 */
char	*expand_exec_name(char *name);
char	**split_path(void);
int		launch_executable(char **argv);

#endif
