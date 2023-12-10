NAME := minishell
CC := cc
SRCDIR := src
INCDIR := include
CFLAGS := -Wall -Wextra -Werror
SOURCE_FILES := \
					reader/reader.c
SOURCES := $(addprefix $(SRCDIR)/,$(SOURCE_FILES))
MAINSOURCE := $(SRCDIR)/minishell.c

INCLUDE_FILES := \
					reader.h \
					config.h
INCLUDES := $(addprefix $(INCDIR)/,$(INCLUDE_FILES))
INC_FLAGS := -I ./$(INCDIR) -lreadline

TESTNAME := minishell_test
TESTFLAGS := -lm -I ./minunit
TESTDIR := test
TESTS := $(TESTDIR)/test.c

all: $(NAME)

$(NAME): $(SOURCES) $(MAINSOURCE) $(INCLUDES)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(SOURCES) $(MAINSOURCE) -o $(NAME)

test: $(TESTNAME)

$(TESTNAME): $(SOURCES) $(TESTS) $(INCLUDES)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(TESTFLAGS) $(SOURCES) $(TESTS) -o $(TESTNAME)

clean:
	rm -f $(NAME) $(TESTNAME)

fclean: clean

re: fclean all

.PHONY: all test clean fclean re
