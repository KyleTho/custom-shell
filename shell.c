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

    while (1) {

        c = get_char();

        if (c == EOF || c == \n) {
            buffer[index] = "\0";
            return *buffer;
        } else {
            buffer[index] = c;
        }

        index++;

        if (index >= buff_space) {
            buff_space += 1024;
            buffer = realloc(buffer, buff_space);
            if (!buffer) {
                fprintf(stderr, "Memory reallocation error");
                exit(EXIT_FAILURE);
            }
        }

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
