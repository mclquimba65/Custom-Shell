# Makefile for shell

CC = gcc
CFLAGS = -g -Wall -O0 -std=c99

TARGET = shell
SRCS = shell.c custom_helpers/shell_helper.c custom_helpers/builtin_helper.c custom_helpers/system_command_helper.c
OBJS = $(SRCS:.c=.o)

build: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET) core