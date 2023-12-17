#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigintHandler(int sig) {
    // Clear the current line
    rl_redisplay();
    printf("\n");
    // Display a new prompt
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	init_signals(void)
{
    signal(SIGINT, sigintHandler);
	signal(SIGQUIT, SIG_IGN);
}

// Function to handle Ctrl+C signal (SIGINT)
void sigintHandler(int sig) {
    // Clear the current line
    rl_redisplay();
    printf("\n");
    // Display a new prompt
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main() {
    // Set the Ctrl+C (SIGINT) signal handler
    signal(SIGINT, sigintHandler);
	signal(SIGQUIT, SIG_IGN);

    // Main loop for reading input lines
    while (1) {
        // Use the GNU Readline library to get a line of input
        char *input = readline("Enter a line: ");

        // Check if the user pressed Ctrl+D (EOF)
        if (input == NULL) {
            printf("\nExiting...\n");
            break;
        }

        // If the input is not empty, add it to the history
        if (input[0] != '\0') {
            add_history(input);
        }

        // Display the input
        printf("You entered: %s\n", input);

        // Free the memory allocated by Readline
        free(input);
    }

    return 0;
}
