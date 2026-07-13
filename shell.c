/* 
   This is a simple UNIX shell written in C.
*/

#include "shell.h"

//void init();
char *read_line(void);
Command *parse_pipeline();
int shell_execute(char **args, int input_source, int dest);


typedef struct{
    char **argv;
    int in_fd;
    int out_fd;
} Command;

/*
* Ensures shell is running in terminal and is the foreground shell of that terminal.
* Needed for adding job control in future.
void init() {

    static pid_t leash_pgid;
    static pid_t leash_pid = getpid();

    is_interactive = isatty(STDIN_FILENO);

    if (is_interactive) {
        // Checks if the PGID of the subshell is the same as the PGID of the foreground of the terminal
        while (tcgetpgrp(STDIN_FILENO) != (leash_pgid = getpgrp())) {
            kill(leash_pid, SIGTTIN);
        }
    }
}
*/

char *read_line(void) {

    char *buffer = NULL;
    size_t buf_size;

    if (getline(&buffer, &buf_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("Could not read line");
            exit(EXIT_FAILURE);
        }
    }

    return buffer;

}


Command *parse_pipeline(char *buffer) {

    Command *commands = malloc(128 * sizeof(Command));
    if (commands == NULL) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }
    
    char *saveptr1, *saveptr2;
    int arg_index;
    char *token;
    char *delims = " \t\r\n";
    
    command = strtok_r(buffer, "|", &saveptr1);
    if (command == NULL) {
        commands[0].argv = NULL;
        return commands;
    }
    
    int i = 0;
    while (command != NULL) {
        token = strtok_r(command, delims, &saveptr2);
        arg_index = 0;
        char **argv = malloc(100 * sizeof(char *));
        if (argv == NULL) {
            fprintf(stderr, "Memory allocation error");
            exit(EXIT_FAILURE);
        }
        while (token != NULL) {
            commands[i].argv[arg_index] = token;
            arg_index++;
            token = strtok_r(NULL, delims, &saveptr2);
        }
        commands[i].argv[arg_index] = NULL;
        commands[i].in_fd = 0;
        commands[i].out_fd = 1;
        i++;
        command = strtok_r(NULL, "|", &saveptr1);
    }

    return commands;

}

    

//    THIS IS FOR EXECUTE FUNCTION
//    First run pipe, then dup() stdin from keyboard to file,
//    then dup2() stdin back to fd[0];
//    while (array of commands not at end)
//        if token is pipe symbol
//            
}

int shell_execute(Command *commands) {
    
    int cpid;
    int cpid_two;
    int status;
    
    //TODO: check for built-ins like "cd"
    if (commands[1].argv == NULL) {
        if (strcmp(comamnds[0].argv[0],"cd") == 0) {
            if (commands[0].argv[1] != NULL) {
                chdir(commands[0].argv[1]);
            }
            return 1;
        }
        else if (strcmp(comamnds[0].argv[0],"exit") == 0) {
            exit(0);
        }
    }
    
    //TODO: check for exit cmd
    // DO these before fork() !!!!!!!!!!!!!!!!

    cpid = fork();

    if (cpid == 0) {
        
        if (execvp(commands[i].argv[0], commands[i].argv) == -1) {
            fprintf(stderr, "Unknown commands");
            exit(EXIT_FAILURE);
        }

    }
    else if (cpid < 0) {
        fprintf(stderr, "Forking error");
    } else {
        waitpid(cpid, &status, WUNTRACED);
    }

    return 1;

} 


int main() {

    char *line = NULL;
    char *commands = NULL;
    int result;

    do {
        
        printf("->");
        line = read_line();
        commands = parse_pipeline(line);
        result = shell_execute(commands);
        
        free(line);
        line = NULL;
        free(commands);
        commands = NULL;
    
    } while(result);
    
}
