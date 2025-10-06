#ifndef SYSTEM_COMMAND_HELPER_H
#define SYSTEM_COMMAND_HELPER_H
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int validate_system_command(char **tokens);
void system_command(char **tokens);

#endif