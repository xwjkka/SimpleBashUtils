#include "s21_grep.h"

int main(int argc, char **argv) {
  parcer(argc, argv);
  return 0;
}

void parcer(int argc, char **argv) {
  regex_t regex;
  int regflags = REG_EXTENDED;

  int opt[10] = {0};

  int ef_f = 1, sf = 0, k = 0;
  char search[4096] = {0};
  int index[256] = {0};

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'e' || argv[i][1] == 'f') {
        ef_f = 0;
      }
    }
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'f') {
        opt[7] = 1;
        read_file(search, argv[i + 1], strlen(search));
        i++;
        ef_f = 0;
      } else if (argv[i][1] == 'e') {
        if (strlen(search) > 0) {
          strcat(search, "|");
        }

        if (strlen(argv[i]) > 2) {
          char *p = (char *)argv[i];
          p += 2;
          strcat(search, p);
        } else if (i + 1 < argc) {
          strcat(search, argv[i + 1]);
          opt[9] = 1;
          ef_f = 0;
          i++;
        }
      } else {
        for (size_t j = 1; j < strlen(argv[i]); j++) {
          if (argv[i][j] == 'i') {
            regflags |= REG_ICASE;
            opt[0] = 1;
          } else if (argv[i][j] == 'v') {
            opt[1] = 1;
          } else if (argv[i][j] == 'c') {
            opt[2] = 1;
          } else if (argv[i][j] == 'l') {
            opt[3] = 1;
          } else if (argv[i][j] == 'n') {
            opt[4] = 1;
          } else if (argv[i][j] == 'h') {
            opt[5] = 1;
          } else if (argv[i][j] == 's') {
            opt[6] = 1;
          } else if (argv[i][j] == 'o') {
            opt[8] = 1;
          }
        }
      }
    } else {
      if (sf || !ef_f) {
        index[k] = i;
        k++;
      }
      if (!sf && ef_f) {
        strcpy(search, argv[i]);
        sf = 1;
      }
    }
  }
  // printf("%s", search);
  for (int j = 0; j < k; j++) {
    if (regcomp(&regex, search, regflags) == 0) {
      fgrep(argv[index[j]], regex, opt, k);
      regfree(&regex);
    }
  }
}

void fgrep(char *name, regex_t regex, int *opt, int pl_f) {
  FILE *input_file = fopen(name, "r");
  int success = REG_NOMATCH;
  regmatch_t match;
  char line[4096] = {0};
  if (input_file == NULL) {
    if (!opt[6]) {
      fprintf(stderr, "No such file or directory\n");
    }
  } else {
    int k = 0;
    int num = 1;
    while (!feof(input_file)) {
      if (fgets(line, sizeof(line), input_file)) {
        success = regexec(&regex, line, 1, &match, 0);
        if ((success == 0 && !opt[1]) || (success == REG_NOMATCH && opt[1])) {
          if (pl_f > 1 && !opt[5] && !opt[3] && !opt[2]) {
            printf("%s:", name);
          }

          if (opt[2]) {
            k++;
          }
          if (opt[3]) {
            break;
          }
          if (opt[4] && !opt[2]) {
            printf("%d:", num);
          }
          if (opt[8] && !opt[2]) {
            char *s = (char *)line;
            while (success == 0) {
              for (int i = match.rm_so; i < match.rm_eo; i++) {
                printf("%c", s[i]);
              }
              printf("\n");
              s += match.rm_eo;
              success = regexec(&regex, s, 1, &match, 0);
            }
          }

          if (!opt[3] && ((!opt[8] || opt[1]) && !opt[2])) {
            printf("%s", line);
            if (feof(input_file)) {
              printf("\n");
            }
          }
        }
        num++;
      }
    }

    if (opt[2]) {
      if (pl_f > 1 && !opt[5]) {
        printf("%s:", name);
      }

      printf("%d\n", k);
    }

    if (opt[3] &&
        ((success == 0 && !opt[1]) || (success == REG_NOMATCH && opt[1]))) {
      printf("%s\n", name);
    }

    fclose(input_file);
  }
}

void read_file(char *search, char *name, int len) {
  FILE *input_file = fopen(name, "r");
  char c;
  int i = len;
  int fl = 0;
  if (len > 0) {
    search[i] = '|';
    i++;
  }
  if (input_file == NULL) {
    fprintf(stderr, "No such file or directory\n");
  } else {
    fscanf(input_file, "%c", &c);
    while (!feof(input_file)) {
      if (c != '\n') {
        search[i] = c;
        fl = 0;
        i++;
      } else if (!fl) {
        search[i] = '|';
        fl = 1;
        i++;
      }
      fscanf(input_file, "%c", &c);
    }
    fclose(input_file);
  }
}
