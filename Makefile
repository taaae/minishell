NAME := minishell
CC := cc
SRCDIR := src
INCDIR := include
CFLAGS := -Wall -Wextra -Werror
SOURCE_FILES := \

SOURCES := $(addprefix $(SRCDIR)/,$(SOURCE_FILES))
MAINSOURCE := $(SRCDIR)/minishell.c

INCLUDE_FILES := \

INCLUDES := $(addprefix $(INCDIR)/,$(INCLUDE_FILES))
INC_FLAGS := -I ./$(INCDIR)

TESTNAME := minishell_test
TESTFLAGS := -lm -I ./minunit
TESTDIR := test
TEST_FILES := \

TESTS := $(addprefix $(TESTDIR)/,$(TEST_FILES))

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
