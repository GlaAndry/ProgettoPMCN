#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
double parse_double(char*string);
long parse_long(char*string);
int parse_integer(char*string);
void check_and_parse_command(char*command,char*filename);
void move_pointer(char**string,int n);
int skip_space(char**string);
char is_blank(char*string);
int parse_integer_and_move(char**string);
long parse_long_and_move(char**string);
double parse_double_and_move(char**string);
int parse_integer_S_from_command_line(int argc,char*argv[],int N);
