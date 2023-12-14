/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:12:42 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/14 17:35:16 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int	parse_double_sym_word(char *line)
{
	if (line[0] == line[1])
		return (2);
	return (1);
}

int	parse_quotes(char *line)
{
	int	i;

	i = 1;
	while (line[i] != '\0' && line[i] != '\'')
		i++;
	if (line[i] != '\0')
		i++;
	return (i);
}

int	parse_dquotes(char *line)
{
	int	i;

	i = 1;
	while (line[i] != '\0' && line[i] != '\"')
		i++;
	if (line[i] != '\0')
		i++;
	return (i);
}

int	parse_word(char *line)
{
	int	i;

	i = 1;
	while (line[i] != '\0' && !ft_isspace(line[i]) \
		&& !ft_in(line[i], WORD_CHARS))
		i++;
	return (i);
}

int	parse_var(char *line)
{
	int	i;

	i = 1;
	if (line[i] == '?')
		return (2);
	while (line[i] != '\0' && (ft_isalnum(line[i]) \
		|| line[i] == '_'))
		i++;
	return (i);
}
