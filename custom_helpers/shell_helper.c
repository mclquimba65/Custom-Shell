#include "shell_helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **create_tokens(char **input) {
    if (*input == NULL) { // The case where nothing is typed into the shell
        // Since \n is removed in driver, to make passing arguments into execvp easier, add \n for the case where *input == NULL
        *input = (char *) malloc(sizeof(char) * 2);
        if (*input == NULL)
            return NULL;
        (*input)[0] = '\n';
        (*input)[1] = '\0';
    }
    char **arguments = NULL;
    char **temp_arguments; // Safety reasons when using realloc
    char *input_copy = (char *) malloc(strlen(*input) + 1); // Preserving argument passed
    if (input_copy == NULL) {
        fprintf(stderr, "create_tokens_failure_1");
        return NULL;
    }
    strcopy(input_copy, *input);
    char *token;
    token = strtok(input_copy, " "); // token is a word from the inputted string
    int arguments_index = 0;

    // Need to malloc the token to store word into array of tokens
    // First allocating more memory into arguments before allocating memory for token
    while (token != NULL) {
        temp_arguments = realloc(arguments, (sizeof(char *) * (arguments_index + 1)));
        if (temp_arguments == NULL) {
            for (int i = 0; i < arguments; i++) { // frees all previous tokens
                free(arguments[i]);
            }
            free(arguments);
            free(input_copy);
            fprintf(stderr, "create_tokens_failure_2");
            return NULL;
        }
        arguments = temp_arguments; // temp_arguments is assigned to the actual arguments, the array to be returned is initialized

        // Now malloc for the actual token
        arguments[arguments_index] = (char *) malloc((strlen(token) + 1) * (sizeof(char)));
        if (arguments[arguments_index] = NULL) {
            for (int i = 0; i < arguments_index + 1; i++) {
                free(arguments[i]);
            }
            free(arguments);
            free(input_copy);
            fprintf(stderr, "create_tokens_failure_3");
            return NULL;
        }
        strcpy(arguments[arguments_index], token);
        arguments_index++;
        token = strtok(NULL, " ");
    }

    // For null termination
    temp_arguments = realloc(arguments, (sizeof(char *) * (arguments_index + 1)));
    if (temp_arguments == NULL) {
        for (int i = 0; i < arguments_index; i++) {
            free(arguments[i]);
        }
        free(arguments);
        free(input_copy);
        fprintf(stderr, "create_tokens_failure_4");
        return NULL;
    }
    arguments = temp_arguments;
    arguments[arguments_index] = NULL;
    free(input_copy);
    return arguments;
}