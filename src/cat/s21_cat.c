#include "s21_cat.h"

int main(int argc, char **argv) {
  char opt = 0;
  int f = 0, v = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      opt = argv[i][1];
      f = 1;
      if (opt == '-') {
        if (strcmp(argv[i], "--number") == 0) {
          opt = 'n';
        } else if (strcmp(argv[i], "--number-nonblank") == 0) {
          opt = 'b';
        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          opt = 's';
        }
      } else if (strcmp(argv[i], "-E") == 0) {
        opt = 'e';
        v = 0;
      } else if (strcmp(argv[i], "-T") == 0) {
        opt = 't';
        v = 0;
      }
    } else {
      fcat(argv[i], opt, f, v);
    }
  }
  return 0;
}

void fcat(char *name, char opt, int f, int v) {
  FILE *input_file = fopen(name, "r");
  char line[256];
  if (input_file == NULL) {
    printf("No such file or directory\n");
  } else {
    int k = 1;

    int p = 0;
    while (!feof(input_file)) {
      if (fgets(line, sizeof(line), input_file)) {
        if (opt == 'b') {
          k = opt_b(line, k);
        } else if (opt == 'n') {
          k = opt_n(line, k);
        } else if (opt == 's') {
          p = opt_s(line, p);
        } else if (f) {
          for (size_t i = 0; i < strlen(line); i++) {
            if (opt == 't') {
              opt_t(line[i], v);
            } else if (opt == 'e') {
              opt_e(line[i], v);
            } else if (opt == 'v') {
              opt_v(line[i]);
            }
          }
        } else {
          printf("%s", line);
        }
      }
    }
    fclose(input_file);
  }
}

void flag_v(char *c) {
  if ((*c >= 0 && *c < 9) || (*c > 10 && *c < 32)) {
    printf("^");
    *c += 64;
  }
}

int opt_b(char *line, int k) {
  if (line[0] != '\n') {
    printf("%6d\t%s", k, line);
    k++;
  } else {
    printf("%s", line);
  }

  return k;
}

int opt_n(char *line, int k) {
  printf("%6d\t%s", k, line);
  k++;

  return k;
}

int opt_s(char *line, int p) {
  if (!(p & (line[0] == '\n'))) {
    printf("%s", line);
    p = 0;
  }

  if (line[0] == '\n') {
    p = 1;
  }

  return p;
}

void opt_e(char c, int v) {
  if (c == '\n') {
    printf("$");
  }
  if (v) {
    flag_v(&c);
  }
  printf("%c", c);
}

void opt_t(char c, int v) {
  if (c == '\t') {
    printf("^I");
  } else {
    if (v) {
      flag_v(&c);
    }
    printf("%c", c);
  }
}

void opt_v(char c) {
  flag_v(&c);
  printf("%c", c);
}
