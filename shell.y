%{

#include "shell.h"

%}


%token NOTOKEN
%token NEWLINE
%token GREAT
%token GREATGREAT
%token GREATAMPERSAND
%token PIPE
%token AMPERSAND
%token WORD

%union{

    char *s_string;
}

%%


