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
 * @prompt: The prompt string to be displayed
 */
void display_prompt(const char *prompt)
{
	printf("%s ", prompt);
	fflush(stdout);
}

/**
 * execute_command - Function to execute commands
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
		if (execve(command, (char *[])
					{
					command,
					NULL
					},
					NULL) == -1)
		{
			perror("./shell");
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
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char buffer[BUFFER_SIZE];

	signal(SIGINT, SIG_IGN);

	const char *prompt = "$";

	if (argc > 1)
	{
		prompt = argv[1];
	}

	while (1)
	{
		display_prompt(prompt);

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
		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}
		execute_command(buffer);
	}
	return (0);
}
