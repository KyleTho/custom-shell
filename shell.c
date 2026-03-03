/* 
   This is a simple UNIX shell written in C.
*/

#include "shell.h"

char *read_line(void);
char **tokenize(char *buffer);
int shell_execute(char **args);


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

int shell_execute(char **args) {
    
    int cpid;
    int status;
    int fd[2];
    pipe(fd);
    cpid = fork();

    if (cpid == 0) {
        
        if (execvp(args[0], args) == -1) {
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
    char **args = NULL;
    int result;

    do {
        
        printf("->");
        line = read_line();
        args = tokenize(line);
        result = shell_execute(args);
        
        free(args);
        args = NULL;
        free(line);
        line = NULL;
    
    } while(result);
    
}

















