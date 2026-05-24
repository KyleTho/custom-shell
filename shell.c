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
* Needed if adding job control in future.
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
    char *token;
    char *delims = " \t\r\n";
    
    command = strtok(buffer, "|");
    if (command == NULL) {
        commands[0] = NULL;
        return commands;
    }
    
    int i = 0;
    while (command != NULL) {
        commands[i] = command;
        i++;
        command = strtok(NULL, "|");
    }

    token = strtok(buffer, delims);
    
    if (token == NULL) {
        tokens[0] = NULL;
    }
    
    int j = 0;
    while (token != NULL) {
        tokens[j] = token;
        j++;
        token = strtok(NULL, delims);
    }

    tokens[i] = NULL;

    return commands;

}

    

//    THIS IS FOR EXECUTE FUNCTION
//    First run pipe, then dup() stdin from keyboard to file,
//    then dup2() stdin back to fd[0];
//    while (array of commands not at end)
//        if token is pipe symbol
//            
}

int shell_execute(char **args) {
    
    int cpid;
    int cpid_two;
    int status;
    
    //TODO: check for built-ins like "cd"
    
    //TODO: check for exit cmd
    // DO these before fork() !!!!!!!!!!!!!!!!

    cpid = fork();

    if (cpid == 0) {
        
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "Unknown commands");
            exit(EXIT_FAILURE);
        }
        
        cpid_two = fork();

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
    char **args = NULL;
    int result;

    do {
        
        printf("->");
        line = read_line();
        args = parse_pipeline(line);
        result = shell_execute(args);
        
        free(args);
        args = NULL;
        free(line);
        line = NULL;
        free(commands);
        commands = NULL;
    
    } while(result);
    
}

