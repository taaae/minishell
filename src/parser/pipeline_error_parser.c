/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_error_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:19 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 18:17:00 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static char	*unexpected_pipe(t_pipeline_token *pipeline_to_free)
{
	free_pipeline(pipeline_to_free);
	return (ft_strdup("minishell: syntax error "
			"near unexpected token `|'"));
}

static char	*unexpected_newline(t_pipeline_token *pipeline_to_free)
{
	free_pipeline(pipeline_to_free);
	return (ft_strdup("minishell: syntax error "
			"near unexpected token `newline'"));
}

static char	*unexpected_tok(t_pipeline_token *pipeline_to_free, const char *tok)
{
	char	*res;

	res = ft_strjoin("minishell: syntax error "
			"near unexpected token: ", tok);
	free_pipeline(pipeline_to_free);
	return (res);
}

char	*pipeline_parse_check(char *line)
{
	t_pipeline_token	*pipeline;
	t_pipeline_token	*pipeline_to_free;

	pipeline = tokenize_pipeline(line);
	pipeline_to_free = pipeline;
	while (pipeline->type != PIPELINE_EOF)
	{
		if (pipeline->type == PIPE && (pipeline[1].type == PIPELINE_EOF
				|| pipeline[1].type == PIPE))
			return (unexpected_pipe(pipeline_to_free));
		if (pipeline->type == REDIRECTION && pipeline[1].type == PIPELINE_EOF)
			return (unexpected_newline(pipeline_to_free));
		if (pipeline->type == REDIRECTION && pipeline[1].type == REDIRECTION)
			return (unexpected_tok(pipeline_to_free, pipeline[1].content));
		pipeline++;
	}
	free_pipeline(pipeline_to_free);
	return (NULL);
}
