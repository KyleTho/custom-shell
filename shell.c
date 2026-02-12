/* 
   This is a limited shell written in C. There is piping functionality,
   but it is limited to two commands. 

*/

char *read_line();
char *tokenize(char *buffer);
int shell_execute(char *token);


char *read_line(void) {

    char *buffer = NULL;
    size_t buf_size;

    if (getline(&buffer, &buf_size, stdin) != -1) {
        if (ferror(stdin)) {

            fprintf(stderr, "Read error")
    
        }   
    }

    return buffer;

}


char **tokenize(char *buffer) {

    char **tokens = malloc(128 * sizeof(char *));
    char *token;
    char *delims = " \t\r\n";

    if (!tokens) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(buffer, delims);
    
    //catches a space or \n input by user
    if (token == NULL) {
        tokens[0] = NULL;
        return tokens;
    }
    
    for (int i=0; token != NULL && i <)
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
    }
    else {
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

















