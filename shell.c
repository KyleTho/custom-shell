/* 
   This is a limited shell written in C. There is piping functionality,
   but it is limited to two commands. 

*/

char *read_line();
char *tokenize(char *buffer);
void shell_execute(char *token);


int main() {

    char *line;
    char **args;

    do {

        fork = 

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

    int buff_space = 1048;
    int index;
    char *buffer = malloc(buff_space);
    int c;

    if (!buffer) {
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
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
