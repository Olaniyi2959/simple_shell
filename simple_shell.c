#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024

/**
 * display_prompt - A function that displays a prompt
 *
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * execute_command - Function to execute cummands
 *
 * @command: A pointer
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(command, (char* [])
					{
					command,
					NULL
					}, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		display_prompt();

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		size_t len = strlen(buffer);

		if (len > 0 && buffer[len - 1] == '\n')
		{
			buffer[len - 1] = '\0';
		}
		execute_command(buffer);
	}
	return (0);
}
