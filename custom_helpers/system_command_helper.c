#include "system_command_helper.h"

int validate_system_command(char **tokens) {
    int tokens_size = 0;
    for (int i = 0; tokens[i] != NULL; i++) { // Gets number of tokens in array
        tokens_size++;
    }
    if (tokens_size == 0)
        return EINVAL
    if (strcmp(tokens[0], "\n") == 0) // If empty string
        return EINVAL
    if (strcmp(tokens[0], "procread") == 0) // Edgecase for procread
        return EINVAL
    return 0;
}

void system_command(char **tokens) {
    int validation = validate_system_command(tokens);
    if (validation != 0)
        return;
    
    // Do fork and exec
    pid_t p = fork();
    if (p < 0) {
        fprintf(stderr, "Fork Failed\n");
    }
    else if (p == 0) { // The process is a child
        execvp(tokens[0], tokens);
        fprintf(stderr, "Child Execution failed\n");
        exit(EXIT_FAILURE);
    }
    else { // The process is a parent
        wait(NULL);
    }
    return;
}