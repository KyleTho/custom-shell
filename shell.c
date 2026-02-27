/* 
   This is a shell written in C. There is piping functionality,
   but it is limited.
*/
#include <shell.h>

char *read_line(void);
char *tokenize(char *buffer);
int shell_execute(char *token);


char *read_line(void) {

    char *buffer = NULL;
    size_t buf_size;

    if (getline(&buffer, &buf_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            prror("Could not read line");
            exit(EXIT_FAILURE)
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
    
    char *token = malloc(sizeof(char));
    if (token == NULL) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }
    
    char *delims = " \t\r\n";

    token = strtok(buffer, delims);
    
    if (token == NULL) {
        tokens[0] = NULL;
        return tokens;
    }
    
    while (token != NULL) {
        token = strtok(NULL, delims);
    }

    return tokens;

}

int shell_execute(char **args) {
    
    int status;
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

    char *line;
    char **args;

    do {
        
        printf("->");
        line = read_line();
        args = tokenize(line);
        result = shell_execute(args);
        free(line);
        line = NULL;
        free(args);
        args = NULL;
    
    } while(result);

}

















