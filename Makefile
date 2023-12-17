NAME := minishell
CC := cc
SRCDIR := src
INCDIR := include
CFLAGS := -Wall -Wextra -Werror -fsanitize=address
SOURCE_FILES := \
					reader/reader.c \
					builtins/builtin_echo.c \
					builtins/builtin_pwd.c \
					builtins/builtin_env.c \
					builtins/builtin_unset.c \
					environment/environment.c \
					environment/environment_utils.c
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
