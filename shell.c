/* 
   This is a limited shell written in C. There is piping functionality,
   but it is limited to two commands. 

*/

char *read_line();
char *tokenize(char *buffer);
int shell_execute(char *token);


int main() {

    char *line;
    char **args;

    do {

        line = read_line();
        args = tokenize(line);
        result = shell_execute(args);
        free(line);
        line = NULL;
        free(args);
        args = NULL;
    
    } while(result);

}


char *read_line() {

    char *buffer = NULL;
    size_t buf_size;

    while (getline(&buffer, &buf_size, stdin) != -1) {

        tokenize(buffer);
    }

    if (ferror(stdin)) {

        fprintf(stderr, "Read error")
    
    }


}

char **tokenize(char *buffer) {

    char **tokens_arr = malloc();

    if (!tokens_arr) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }

    char *token = malloc();

    if (!token) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = str_tok();


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



















