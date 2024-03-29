NAME := minishell
CC := cc
SRCDIR := src
INCDIR := include
CFLAGS := -Wall -Wextra -Werror -g -ggdb
# CFLAGS := -Wall -Wextra -Werror -g -ggdb -fsanitize=address
SOURCE_FILES := \
			builtins/builtin_cd.c \
			builtins/builtin_echo.c \
			builtins/builtin_env.c \
			builtins/builtin_exit.c \
			builtins/builtin_export.c \
			builtins/builtin_pwd.c \
			builtins/builtin_unset.c \
			environment/environment.c \
			environment/environment_utils.c \
			environment/environment_utils2.c \
			exec_finder/exec_finder.c \
			exec_finder/exec_finder_utils.c \
			exec_finder/exec_launcher.c \
			expansions/star_expand.c \
			expansions/star_expand_file_utils.c \
			expansions/var_expand.c \
			lexer/quotes_and_parens.c \
			lexer/token_composer.c \
			lexer/token_string_utils.c \
			lexer/tokenizer.c \
			logic_tokenizer/logic_tokenizer.c \
			logic_tokenizer/logic_tokenizer_utils.c \
			logic_tokenizer/logic_tokenizer_utils2.c \
			parser/arg_tokenizer.c \
			parser/command_executer.c \
			parser/expander.c \
			parser/logic_error_parser.c \
			parser/logic_executer.c \
			parser/pipeline_error_parser.c \
			parser/pipeline_executer.c \
			parser/pipeline_lexer.c \
			parser/pipeline_lexer_next_token.c \
			reader/heredoc_utils.c \
			reader/heredoc_utils2.c \
			reader/read_heredoc.c \
			reader/reader.c \
			signals/signals.c \
			signals/signals_child.c \
			global_code.c
SOURCES := $(addprefix $(SRCDIR)/,$(SOURCE_FILES))
MAINSOURCE := $(SRCDIR)/minishell.c

LIBFTDIR=libft
LIBFT=$(LIBFTDIR)/libft.a

INCLUDE_FILES := \
					builtins.h \
					config.h \
					environment.h \
					reader.h
INCLUDES := $(addprefix $(INCDIR)/,$(INCLUDE_FILES))
INC_FLAGS := -I ./$(INCDIR) -I ./libft -L ./libft -lft -lreadline

TESTNAME := minishell_test
TESTFLAGS := -lm -I ./minunit
TESTDIR := test
TESTS := $(TESTDIR)/test.c

all: $(NAME)

$(NAME): $(SOURCES) $(MAINSOURCE) $(INCLUDES) $(LIBFT)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(SOURCES) $(MAINSOURCE) -o $(NAME)

test: $(TESTNAME)

$(TESTNAME): $(SOURCES) $(TESTS) $(INCLUDES) $(LIBFT)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(TESTFLAGS) $(SOURCES) $(TESTS) -o $(TESTNAME)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	make -C $(LIBFTDIR) fclean

fclean: clean
	rm -f $(NAME) $(TESTNAME)

re: fclean all

.PHONY: all test clean fclean re
