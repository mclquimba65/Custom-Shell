#include "builtin_helper.h"

int b_exit(char **tokens, char *input) {
    // First check if tokens is empty
    // Then check if tokens[0] is exit
    // Then check if there are more args
    int tokens_size = 0;
    for (int i = 0; tokens[i] != NULL; i++) {
        tokens_size++;
    }
    if (tokens_size < 1)
        return ESRCH;
    if (strcmp(tokens[0], "exit") != 0)
        return EINVAL;
    if (tokens_size > 1) {
        fprintf(stderr, "ERROR: Invalid Argument Size\n");
        return E2BIG;
    }

    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
    free(input);
    return 0;
}

int history(char **tokens, FILE *history) {
    // First check if tokens is empty
    // Then check if tokens[0] is history
    // Then check if there are more args
    int tokens_size = 0;
    for (int i = 0; tokens[i] != NULL; i++) {
        tokens_size++;
    }
    if (tokens_size < 1)
        return ESRCH;
    if (strcmp(tokens[0], "history") != 0)
        return EINVAL;
    if (tokens_size > 1) {
        printf("ERROR: Invalid Argument Size\n");
        return E2BIG;
    }

    fseek(history, 0, SEEK_SET);
    char *file_ptr = NULL;
    size_t file_ptr_length = 0;
    int num_lines = 0;
    ssize_t getline_return = 0;

    // First get # of lines in file
    do {
        getline_return = getline(&file_ptr, &file_ptr_length, history);
        if (getline_return >= 0)
            num_lines++;
    } while (getline_return >= 0);
    fseek(history, 0, SEEK_SET);
    getline_return = 0;

    // Now read 10 lines earlier
    // -11 to account for history
    int adjusted_num_lines = num_lines - 11;
    int current_line_num = 0;
    if (adjusted_num_lines < 0)
        adjusted_num_lines = 0;
    
    // Move to 10 before history call
    while (current_line_num < adjusted_num_lines) {
        getline(&file_ptr, &file_ptr_length, history);
        current_line_num++;
    }

    // Print the 10 calls before history
    while (current_line_num < num_lines - 1) {
        getline(&file_ptr, &file_ptr_length, history);
        printf("%s", file_ptr);
        current_line_num++;
    }

    // Go to the end of the file
    fseek(history, 0, SEEK_END);
    free(file_ptr);
    return 0;
}

int procread(char **tokens) {
    // Validate first
    int validation = validate_procread(tokens);
    if (validation != 0)
        return validation;

    char *concat_string = NULL;
    concat_string = (char *) malloc((sizeof(char)) * (strlen("/proc/") + strlen(tokens[1]) + 1));
    if (concat_string = NULL)
        return ENOMEM;

    // Reading proc file, so must append /proc/ to access file
    strcpy(concat_string, "/proc/");
    strcat(concat_string, tokens[1]);

    char *proc_line = NULL;
    size_t proc_line_size = 0;
    FILE *proc_file = fopen(concat_string, "r");
    if (proc_file == NULL) {
        fprintf(stderr, "ERROR: File not found\n");
        free(concat_string);
        return ENOENT;
    }
    ssize_t getline_return = 0;
    do {
        getline_return = getline(&proc_line, &proc_line_size, proc_file);
        if (getline_return >= 0)
            printf("%s", proc_line);
    } while (getline_return >= 0);

    fclose(proc_file);
    free(concat_string);
    free(proc_line);
    return 0;
}

int validate_procread(char **tokens) {
    // First check if tokens is empty
    // Then check if tokens[0] is procread
    // Then check if tokens has no args
    // Then check if tokens has > 1 args
    // Then check if that arg has lead /
    int tokens_size = 0;
    for (int i = 0; tokens[i] != NULL; i++) {
        tokens_size++;
    }
    if (tokens_size < 1)
        return ESRCH;
    if (strcmp(tokens[0], "procread") != 0)
        return EINVAL;
    if (tokens_size < 2) {
        fprintf(stderr, "ERROR: One argument is required\n");
        return EINVAL;
    }
    if (tokens_size > 2) {
        fprintf(stderr, "ERROR: Only a single argument is allowed\n");
        return E2BIG;
    }
    if (tokens[1][0] == '/') {
        fprintf(stderr, "ERROR: File cannot start with \"/\"\n");
        return ENOENT;
    }
    return 0;
}