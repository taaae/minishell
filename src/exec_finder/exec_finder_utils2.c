/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:47:58 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/23 21:12:15 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**split_path(void)
{
	char	**s;

	s = calloc(11, sizeof(char *));
	s[0] = ft_strdup("/var/tmp/");
	s[1] = ft_strdup("/Users/lporoshi/.brew/bin");
	s[2] = ft_strdup("/usr/local/bin");
	s[3] = ft_strdup("/bin");
	s[4] = ft_strdup("/usr/sbin");
	s[5] = ft_strdup("/usr/bin");
	s[6] = ft_strdup("c");
	s[7] = ft_strdup("d");
	s[8] = ft_strdup("e");
	s[9] = ft_strdup("f");
	s[10] = NULL;
	return (s);
}
