#include "custom_helpers/shell_helper.h"
#include "custom_helpers/builtin_helper.h"
#include "custom_helpers/system_command_helper.h"

int main() {
    char *shell_input = NULL;
    size_t shell_input_size = 0;
    char **tokens = NULL;

    FILE *f_history = fopen(".shellHistory", "w+");
    
    // Starting shell loop
    while (1) {
        printf("Simple Shell > ");
        fflush(stdout); // Used to make sure previous printf statement is printed to the terminal
        getline(&shell_input, &shell_input_size, stdin); // Retrieves user input
        fprintf(f_history, "%s", shell_input);

        // strtok to remove \n
        shell_input = strtok(shell_input, "\n");
        // Parsing command
        tokens = create_tokens(&shell_input);
        if (tokens == NULL) {
            fprintf(stderr, "Parsing error\n");
            return 1;
        }

        if (b_exit(tokens, shell_input) == 0) {
            printf("Exiting Simple Shell\n");
            fclose(f_history);
            return 0;
        }
        else if (history(tokens, f_history) == 0) {
            printf("History called\n");
        }
        else if (procread(tokens) == 0) {
            printf("Procread called\n");
        }
        else {
            system_command(tokens);
        }
    }
}