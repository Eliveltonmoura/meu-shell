#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

/**
 ** @brief Launch a program and wait for it to terminate.
 ** @param args Null terminated list of arguments (including program).
 ** @return Always returns 1, to continue execution.
 */

#define HISTORY_SIZE 100
char *history[HISTORY_SIZE];
int history_count = 0;

void add_history(char *line)
{
    if (history_count < HISTORY_SIZE)
    {
       
        line[strcspn(line, "\n")] = '\0';

      
        char *copy = malloc(strlen(line) + 1);
        if (copy != NULL)
        {
            strcpy(copy, line);
            history[history_count++] = copy;
        }
    }
}

int sh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        

       
        for (int i = 0; args[i] != NULL; i++)
        {
            if (strcmp(args[i], ">") == 0)
            {
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[i] = NULL;
                break;
            }
            else if (strcmp(args[i], "<") == 0)
            {
                int fd = open(args[i + 1], O_RDONLY);
                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                args[i] = NULL;
                break;
            }
        }

       
        if (execvp(args[0], args) == -1)
        {
            perror("sh238p");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("sh238p");
    }
    else
    {
        
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1; 
}

/**
 ** @brief 
 ** @param args
 ** @return 
 */
int sh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    return 1;

    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "sh238p: esperado argumento para \"cd\"\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
                perror("sh238p");
        }
        return 1;
    }
    if (strcmp(args[0], "exit") == 0)
    {
        return 0; 
    }
    if (strcmp(args[0], "history") == 0)
    {
        for (int i = 0; i < history_count; i++)
        {
            printf("%d %s\n", i + 1, history[i]);
        }
        return 1;
    }

    return sh_launch(args); 
}

/**
 ** @brief 
 ** @param line 
 ** @return
 */
#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\r\n\a"
char **sh_split_line(char *line)
{
    int bufsize = SH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens)
    {
        fprintf(stderr, "sh238p: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SH_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += SH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                free(tokens_backup);
                fprintf(stderr, "sh238p: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

/**
 ** @brief Read a line of input from stdin.
 ** @return The line from stdin.
 **/
char *sh_read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0; 
    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        { // We recieved an EOF
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("sh238p: sh_read_line");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

/**
 ** @brief
 **/
void sh_loop(void)
{

    char *line;
    char **args;
    int status;

    do
    {
        printf("238p$ ");
        line = sh_read_line();
        add_history(line);
        args = sh_split_line(line);
        status = sh_execute(args);
        free(line);
        free(args);
    } while (status);
}

/**
 ** @brief Main entry point.
 ** @param argc Argument count.
 ** @param argv Argument vector.
 ** @return status code
 **/
int main(int argc, char **argv)
{
    sh_loop();
    return EXIT_SUCCESS;
}
