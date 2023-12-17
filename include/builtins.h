/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:31:39 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/17 16:16:39 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

int	builtin_echo(char **argv, bool no_newline_flag);
int	builtin_pwd(char **argv);
int	builtin_env(char **argv);
int	builtin_export(char **argv);
int	builtin_unset(char **argv);

#endif