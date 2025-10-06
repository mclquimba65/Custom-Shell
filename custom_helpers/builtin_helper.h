#ifndef BUILTIN_HELPER_H
#define BUILTIN_HELPER_H
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int b_exit(char **tokens, char *input);
int history(char **tokens, FILE *history);
int procread(char **tokens);

int validate_procread(char **tokens);
#endif