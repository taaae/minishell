/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:31:39 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/18 17:18:14 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

int	builtin_echo(char **argv, bool no_newline_flag);
int	builtin_pwd(void);
int	builtin_env(char **argv);
int	builtin_export(char **argv);
int	builtin_unset(char **argv);

#endif
