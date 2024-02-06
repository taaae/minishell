/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:06 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/06 19:19:43 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "logic_tokenizer.h"
# include "libft.h"

char				*logic_parse_check(t_logic_token **token);
int					exec_logic(t_logic_token **token);
char				*pipeline_parse_check(char *command);
int					exec_pipeline(char *command);

typedef enum e_pipeline_token_type {
	ARG,
	REDIRECTION,
	PIPE,
	PIPELINE_EOF
}	t_pipeline_token_type;

typedef struct s_pipeline_token
{
	t_pipeline_token_type	type;
	char					*content;
}	t_pipeline_token;

int					exec_command(t_pipeline_token *pipeline);

t_pipeline_token	*tokenize_pipeline(char *pipeline);
t_pipeline_token	next_token(char **str);
void				free_pipeline(t_pipeline_token *pipeline);

typedef enum e_arg_token_type
{
	NORMAL_ARG,
	DQUOTED,
	SQUOTED,
}	t_arg_token_type;

typedef struct s_arg_token
{
	t_arg_token_type	type;
	char				*content;
}	t_arg_token;

t_list				*tokenize_arg(char *arg);
void				expand_vars(char **str);

#endif
