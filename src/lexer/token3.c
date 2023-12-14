/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:12:42 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/14 15:21:56 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// for "$" if next is not alnum, interpret as "$" // if ? then you know
/*
	if (line[i] == '\'')
		return (parse_quotes(line));
	if (line[i] == '\"')
		return (parse_dquotes(line));
	if (ft_isalnum(line[i]) || line[i] == '*' || line == '-')
		return (parse_word(line));
	if (line[i] == '$')
		return (parse_var(line));
*/
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
	while (line[i] != '\0' && !ft_isspace(line[i]))
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
