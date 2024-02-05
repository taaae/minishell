/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:03:15 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/05 14:07:56 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "environment.h"
#include "expansions.h"
#include <fcntl.h>
#include "exec_find.h"

static int  pipe_num(const t_pipeline_token *pipeline)
{
	int res = 0;

	while (pipeline->type != PIPELINE_EOF)
	{
		res += (pipeline->type == PIPE);
		pipeline++;
	}
	return (res);
}

//char    **expand_arg(char *arg)
//{
//    char **expanded;
//
//    expanded = ft_calloc(2, sizeof(char *));
//    expanded[0] = arg;
//    return (expanded);
//}

char	**expand_arg(char *arg)
{
	char	*expanded_str;
	char	**res;
	// [0] == " -> expand vars, return substr(1, len - 2)
	// [0] == ' -> return substr(1, len - 2)
	// else -> expand vars, expand wildcards, return split
	if (arg[0] == '\'')
	{
		res = ft_calloc(2, sizeof(char *));
		expanded_str = ft_substr(arg, 1, ft_strlen(arg) - 2);
		res[0] = expanded_str;
		return (res);
	}
	if (arg[0] == '"')
	{
		res = ft_calloc(2, sizeof(char *));
		expanded_str = ft_substr(arg, 1, ft_strlen(arg) - 2);
		expand_vars(&expanded_str);
		res[0] = expanded_str;
		return (res);
	}
	expanded_str = ft_strdup(arg);
	expand_vars(&expanded_str);
	expanded_str = expand_stars_string(expanded_str);
	res = ft_split(expanded_str, ' ');
	free(expanded_str);
	return (res);
}

char	**add_arg(char **argv, char *arg)
{
	int		n;
	int		m;
	char	**new;
	char	**expanded;

	expanded = expand_arg(arg);
	n = 0;
	new = argv;
	while (*new != NULL)
	{
		new++;
		n++;
	}
	m = 0;
	new = expanded;
	while (*new != NULL)
	{
		new++;
		m++;
	}
	new = ft_calloc(n + m + 1, sizeof(char *));
	n = 0;
	while (argv[n] != NULL)
	{
		new[n] = argv[n];
		n++;
	}
	m = 0;
	while (expanded[m] != NULL)
	{
		new[n + m] = expanded[m];
		m++;
	}
	free(argv);
	free(expanded);
	return (new);
}

int	handle_redirection(const t_pipeline_token *pipeline)
{
	int	fd;

	if (pipeline->content[0] == '<')
	{
		fd = open(pipeline[1].content, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (pipeline->content[0] == '>' && pipeline->content[1] == '\0')
	{
		fd = open(pipeline[1].content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (pipeline->content[0] == '>' && pipeline->content[1] == '>')
	{
		fd = open(pipeline[1].content, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	pipeline++;
	return (0);
}

// temp func
char	*merge_args(char **strings) {
	// Calculate total length needed
	int total_length = 0;
	for (int i = 0; strings[i] != NULL; i++) {
		total_length += strlen(strings[i]) + 1; // +1 for space or NULL terminator
	}

	if (total_length == 0) {
		return NULL; // No strings to merge
	}

	// Allocate memory for the merged string
	char *merged = malloc(total_length * sizeof(char));
	if (merged == NULL) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	// Initialize the first character to the end of string to support strcat operation
	merged[0] = '\0';

	// Concatenate strings
	for (int i = 0; strings[i] != NULL; i++) {
		strcat(merged, strings[i]);
		if (strings[i + 1] != NULL) { // Check if not the last string
			strcat(merged, " "); // Add a space between words
		}
	}

	return merged;
}

void exec_command(t_pipeline_token *pipeline)
{
	int     code;
	char    **argv;

	argv = ft_calloc(1, sizeof(char *));
	while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
	{
		if (pipeline->type == REDIRECTION)
		{
			code = handle_redirection(pipeline); // expand everything here and output error if fail code probably 1 or 0
			if (code == 1)
			{
//                free_argv(argv);
				exit(code);
			}
			pipeline++;
		}
		else
			argv = add_arg(argv, pipeline->content);
		pipeline++;
	}
//    exit (system(merge_args(argv))); // fake
    launch_executable(argv);
//	write(2, merge_args(argv), strlen(merge_args(argv)));
//	exit(0);
//    execve(argv[0], argv + 1, get_environ()); // idk if argv + 1 is good, might need to reallocate to size 1 less. also need to execute the actual executable, not its name (search PATH and builtins)
	// might need to free more stuff
//    exit(127); // error not always "command not found", check errno for possible errors
}

int         exec_pipeline(char *command)
{
    // TODO: make it without subshell if no pipes
	t_pipeline_token	*pipeline;
	t_pipeline_token	*pipeline_to_free;
	int					n;
	int					n2;
	int					p[2];
	int					prev_in;
	int					code;
	int					pid;

	pipeline = tokenize_pipeline(command);
	pipeline_to_free = pipeline;
	n = pipe_num(pipeline) + 1;
	n2 = n;
	prev_in = STDIN_FILENO;
	while (n--)
	{
		if (n != 0)
			pipe(p);
		pid = fork();
		if (pid == 0) {
			//call signal handler here
			//init_sig_child();
			dup2(prev_in, STDIN_FILENO);
			if (prev_in != STDIN_FILENO)
				close(prev_in);
			if (n != 0) {
				dup2(p[1], STDOUT_FILENO);
				close(p[1]);
			}
			exec_command(pipeline);
		}
		if (prev_in != STDIN_FILENO)
			close(prev_in);
		close(p[1]);
		prev_in = p[0];
		while (pipeline->type != PIPELINE_EOF && pipeline->type != PIPE)
			pipeline++;
		pipeline++;
	}
	waitpid(pid, &code, 0);
	while (n2--)
		wait(NULL);
	free_pipeline(pipeline_to_free);
	return (WEXITSTATUS(code));
}
