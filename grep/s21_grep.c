#include "s21_grep.h"

/*grep [options] template [file_name] */

int main(int argc, char **argv)

{
  regex_t regex;
  KEYS keys = {0};

  if (argc > 2) {
    Keys_Expressions(&regex, argc, argv, &keys, Pattern);
    FileReader(&regex, argv, argc, keys);
  }

  return 0;
}

void Keys_Expressions(regex_t *regex, int argc, char **argv, KEYS *keys,
                      char *Pattern) {
  int inputKey;
  int NumE = 0;
  // int TEMP;

  while ((inputKey = getopt(argc, argv, "e:ivcln")) != -1) {
    if (inputKey == 'e') {
      keys->e = 1;
      if (NumE != 0) strcat(Pattern, "|\0");
      strcat(Pattern, optarg);
      NumE++;
      keys->SUM++;
    } else if (inputKey == 'i') {
      keys->i = 1;
      keys->SUM++;
    } else if (inputKey == 'v') {
      keys->v = 1;
      keys->SUM++;
    } else if (inputKey == 'c') {
      keys->c = 1;
      keys->SUM++;
    } else if (inputKey == 'l') {
      keys->l = 1;
      keys->SUM++;
    } else if (inputKey == 'n') {
      keys->n = 1;
      keys->SUM++;
    } else
      keys->err = 1;
  }

  // printf("key e = %d\n", keys->e);
  // printf("key i = %d\n", keys->i);
  // printf("key v = %d\n", keys->v);
  // printf("key c = %d\n", keys->c);
  // printf("key l = %d\n", keys->l);
  // printf("key n = %d\n", keys->n);
  // printf("key err = %d\n", keys->err);
  // printf("key SUM = %d\n", keys->SUM);

  if (keys->err == 0 && keys->SUM != 0) {
    if (keys->e && !keys->i) {
      regcomp(regex, Pattern, REG_EXTENDED);
    }

    if (!keys->e && keys->i) {
      strcat(Pattern, argv[optind]);
      regcomp(regex, Pattern, REG_ICASE);
    }

    if (keys->e && keys->i) {
      regcomp(regex, Pattern, REG_EXTENDED | REG_ICASE);
    }

    if (!keys->i && !keys->e && (keys->v || keys->c || keys->l || keys->n)) {
      strcat(Pattern, argv[optind]);
      regcomp(regex, Pattern, 0);
    }
  } else if (keys->err == 0 && keys->SUM == 0) {
    strcat(Pattern, argv[optind]);
    regcomp(regex, Pattern, 0);
  }
}

void FileReader(regex_t *regex, char **argv, int argc, KEYS keys) {
  if (!keys.err) {
    for (int K = 1; K < argc; K++) {
      char *FileStrBuff = NULL;
      int myREGEX;
      size_t size = 0;
      int number_line = 1;
      int CorrelativeLines = 0;
      int NUMFILES = argc - optind;
      FILE *fptr;
      fptr = fopen(argv[K], "r");

      if (fptr != NULL)  // further file can be opened
      {
        while ((getline(&FileStrBuff, &size, fptr)) != -1) {
          myREGEX = regexec(regex, FileStrBuff, 0, NULL, 0);
          if (keys.v) {
            myREGEX = !myREGEX;
          }

          if (myREGEX == 0) {
            CorrelativeLines++;
            if (keys.n && !keys.c && !keys.l) {
              if (NUMFILES > 2)
                printf("%s:%d:%s", argv[K], number_line, FileStrBuff);
              else
                printf("%d:%s", number_line, FileStrBuff);
              if (FileStrBuff[strlen(FileStrBuff) - 1] != '\n') printf("\n");

            } else if (!keys.c && !keys.l && !keys.n) {
              if (NUMFILES > 2)
                printf("%s:%s", argv[K], FileStrBuff);
              else
                printf("%s", FileStrBuff);
              if (FileStrBuff[strlen(FileStrBuff) - 1] != '\n') printf("\n");
            }
            // if (FileStrBuff[strlen(FileStrBuff) - 1] != '\n') printf("\n");
          }
          number_line++;
        }

        if (keys.c && !keys.l) {
          if (NUMFILES > 2)
            printf("%s:%d\n", argv[K], CorrelativeLines);
          else
            printf("%d\n", CorrelativeLines);
        }

        if (keys.l && !keys.c && CorrelativeLines != 0) {
          printf("%s\n", argv[K]);
        }

        if (keys.c && keys.l) {
          int OUT_CL;
          if (CorrelativeLines != 0)
            OUT_CL = 1;
          else
            OUT_CL = 0;

          if (NUMFILES > 2)
            printf("%s:%d\n", argv[K], OUT_CL);
          else
            printf("%d\n", OUT_CL);

          if (CorrelativeLines != 0) printf("%s\n", argv[K]);
        }

        free(FileStrBuff);
        fclose(fptr);
      }
    }
    regfree(regex);
  }
}