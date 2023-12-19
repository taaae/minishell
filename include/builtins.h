/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:31:39 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 15:54:26 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

int	builtin_echo(int argc, char **argv);
int	builtin_pwd(int argc, char **argv);
int	builtin_env(int argc, char **argv);
int	builtin_export(int argc, char **argv);
int	builtin_unset(int argc, char **argv);

#endif
