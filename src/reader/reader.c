/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:15:07 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/09 16:51:19 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/reader.h"

void	init_reader(void)
{
	using_history();
}

void	close_reader(void)
{
	rl_clear_history();
}

char	*get_line(void)
{
	char			*line;

	line = readline("minishell$ ");
	if (line == NULL || line[0] == '\0')
		return (NULL);
	add_history(line);
	return (line);
}
