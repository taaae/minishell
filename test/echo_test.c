/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:02:21 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/09 18:06:37 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"
#include <string.h>

//"", false
//
int	main(int argc, char **argv)
{
	argv[1] = strdup("lol\c");
	echo(argv, false);
}
