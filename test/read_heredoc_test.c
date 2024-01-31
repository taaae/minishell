/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:40:02 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/31 19:42:58 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "reader.h"

char	*expand_exec_name(char *name);

extern char	**environ;

int	main(void)
{
	char	*line;
	char	*res_line;

	line = ft_strdup("cat <<A <<A <<B <<B");
	ft_printf("from: [%s]\n", line);
	res_line = read_heredocs(line);
	ft_printf("to  : [%s]\n", res_line);
	free(res_line);
	return (0);
}
