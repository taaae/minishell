/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:21 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 18:21:51 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	free_pipeline(t_pipeline_token *pipeline)
{
	t_pipeline_token	*ptr;

	ptr = pipeline;
	while (ptr->type != PIPELINE_EOF)
	{
		if (ptr->type != PIPE)
			free(ptr->content);
		ptr++;
	}
	free(pipeline);
}

static void	pipeline_append(t_pipeline_token **arr, t_pipeline_token new)
{
	size_t				i;
	t_pipeline_token	*res;

	i = 0;
	while ((*arr)[i].type != PIPELINE_EOF)
		i++;
	res = (t_pipeline_token *)malloc((i + 2) * sizeof(t_pipeline_token));
	i = 0;
	while ((*arr)[i].type != PIPELINE_EOF)
	{
		res[i] = (*arr)[i];
		i++;
	}
	res[i].type = new.type;
	res[i].content = new.content;
	res[i + 1] = (*arr)[i];
	free(*arr);
	*arr = res;
}

t_pipeline_token	*tokenize_pipeline(char *pipeline)
{
	t_pipeline_token	*res;
	t_pipeline_token	next;

	res = malloc(sizeof(t_pipeline_token));
	res[0].type = PIPELINE_EOF;
	res[0].content = NULL;
	while (*pipeline != '\0')
	{
		while (ft_isspace(*pipeline))
			pipeline++;
		if (*pipeline == '\0')
			break ;
		next = next_token(&pipeline);
		pipeline_append(&res, next);
	}
	return (res);
}
