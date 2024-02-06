/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:11:42 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/19 14:41:05 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	parse_two_sym_word(char *line)
{
	if (line[0] == line[1])
		return (2);
	return (1);
}

static int	parse_quotes(char *line, const char quote)
{
	int	i;

	i = 1;
	while (line[i] != '\0' && line[i] != quote)
		i++;
	if (line[i] == '\0')
		return (0);
	i++;
	return (i);
}

static int	parse_word(char *line)
{
	int	i;

	i = 1;
	while (line[i] != '\0' && !ft_isspace(line[i]) && !ft_in(line[i],
			WORD_CHARS))
		i++;
	return (i);
}

static int	parse_var(char *line)
{
	int	i;

	i = 1;
	if (line[i] == '?')
		return (2);
	while (line[i] != '\0' && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}

int	get_next_tok_len(char *line)
{
	int	i;

	i = 0;
	if (ft_in(line[i], ONE_SYM_WORDS))
		return (1);
	if (ft_in(line[i], TWO_SYM_WORDS))
		return (parse_two_sym_word(line + i));
	if (line[i] == '\'' || line[i] == '\"')
		return (parse_quotes(line + i, line[i]));
	if (line[i] == '$')
		return (parse_var(line + i));
	return (parse_word(line + i));
}
