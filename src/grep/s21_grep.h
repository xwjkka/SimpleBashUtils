#include <regex.h>
#include <stdio.h>
#include <string.h>

void fgrep(char *name, regex_t regex, int *opt, int pl_f);
void read_file(char *search, char *name, int len);
int sum_m(int *arr);
void parcer(int argc, char **argv);
