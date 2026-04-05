/* 
   This is a simple UNIX shell written in C.
*/

#include "shell.h"

void init();
char *read_line(void);
char **tokenize(char *buffer);
void pipe_cmd(char **args);
int shell_execute(char **args, int input_source, int dest);


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


char **tokenize(char *buffer) {

    char **tokens = malloc(128 * sizeof(char *));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }
    char *token;
    
    char *delims = " \t\r\n";
    int i = 0;

    token = strtok(buffer, delims);
    
    if (token == NULL) {
        tokens[0] = NULL;
        return tokens;
    }
    
    while (token != NULL) {
        token = strtok(NULL, delims);
        tokens[i] = token;
        i++;
    }

    tokens[i] = NULL;

    return tokens;

}

void pipe_cmd(char **args) {
    int fd[2];
    int input_source = 0;
    int length = sizeof(**args) / sizeof(*args);
    
    for (int i=0; args[i] != NULL; i++) {
        
        if (args[i+1] != NULL) {
            
        }
        
    }
    
    
    
    
    
    
    
//    First run pipe, then dup() stdin from keyboard to file,
//    then dup2() stdin back to fd[0];
//    while (array of tokens not at end)
//        if token is pipe symbol
//            
}

int shell_execute(char **args) {
    
    int cpid;
    int cpid_two;
    int status;

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
        args = tokenize(line);
        result = pipe_cmd(args);
        
        free(args);
        args = NULL;
        free(line);
        line = NULL;
    
    } while(result);
    
}

















