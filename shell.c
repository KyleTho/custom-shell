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
