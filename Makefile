NAME := minishell
CC := cc
SRCDIR := src
INCDIR := include
CFLAGS := -Wall -Wextra -Werror
SOURCE_FILES := \
					reader/reader.c \
					builtins/echo.c
SOURCES := $(addprefix $(SRCDIR)/,$(SOURCE_FILES))
MAINSOURCE := $(SRCDIR)/minishell.c


LIBFTDIR=libft
LIBFT=$(LIBFTDIR)/libft.a

INCLUDE_FILES := \
					reader.h \
					config.h
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
