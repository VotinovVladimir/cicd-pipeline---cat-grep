#include <stdio.h>
#include <string.h>

void KeyChecker(int argc, char *argv[], int *KeyValues);
void File_Printer(int argc, char *argv[], int *KeyValues);
void benstv_Functions(FILE *fptr, int *KeyValues);

int main(int argc, char *argv[]) {
  int KeyValues[7] = {0};
  KeyChecker(argc, argv, KeyValues);
  File_Printer(argc, argv, KeyValues);

  return 0;
}

void File_Printer(int argc, char *argv[], int *KeyValues) {
  if (KeyValues[6] == 0) {
    FILE *fptr;

    for (int i = 1; i < argc; i++) {
      char *testvar = argv[i];

      if (testvar[0] != '-')  // lookin only files
      {
        fptr = fopen(argv[i], "r");
        if (fptr != NULL)  // further file can be opened
        {
          benstv_Functions(fptr, KeyValues);

          fclose(fptr);
        } else
          printf("ERR-FILE");
      }
    }
  } else
    printf("ERR-KEY");
}

void KeyChecker(int argc, char *argv[], int *KeyValues) {
  for (int i = 1; (i < argc) && KeyValues[6] == 0; i++) {
    char *testvar = argv[i];

    if (testvar[0] == '-' && testvar[1] == '\0')
      KeyValues[6] = 1;

    else if (testvar[0] == '-' && testvar[1] != '-') {
      for (int k = 1; testvar[k] != '\0'; k++) {
        if (testvar[k] == 'b')
          KeyValues[0] = 1;

        else if (testvar[k] == 'e')
          KeyValues[1] = 1;

        else if (testvar[k] == 'n')
          KeyValues[2] = 1;

        else if (testvar[k] == 's')
          KeyValues[3] = 1;

        else if (testvar[k] == 't')
          KeyValues[4] = 1;

        else if (testvar[k] == 'v')
          KeyValues[5] = 1;

        else
          KeyValues[6] = 1;  // wrong key among input ARGV ->> stop
      }
    } else if (testvar[0] == '-' && testvar[1] == '-') {
      if (!strcmp(argv[i], "--number-nonblank"))
        KeyValues[0] = 1;

      else if (!strcmp(argv[i], "--squeeze-blank"))
        KeyValues[3] = 1;

      else if (!strcmp(argv[i], "--number"))
        KeyValues[2] = 1;

      else
        KeyValues[6] = 1;
    }
  }
}

void benstv_Functions(FILE *fptr, int *KeyValues) {
  int strings = 1;
  int count = 1;
  int empty = 0;
  // int T_mode = 0;
  // int E_mode = 0;

  char Symb;

  while ((Symb = fgetc(fptr)) != EOF) {
    if (KeyValues[0] && count && Symb != '\n') {
      printf("%6d\t", strings);
      strings++;
      count = 0;
    }

    if (KeyValues[2] && count && KeyValues[0] == 0) {
      printf("%6d\t", strings);
      strings++;
      count = 0;
    }

    if (KeyValues[3]) {
      if (Symb == '\n') {
        ++empty;
        if (empty > 2) {
          continue;
        }
      } else {
        empty = 0;
      }
    }

    // if (KeyValues[1] && Symb == '\n' ) {
    //     printf("$");
    // }

    if (KeyValues[4] && Symb == '\t') {
      printf("^");
      Symb = 'I';
      // T_mode = 1;
    }

    if ((KeyValues[5] || KeyValues[4] || KeyValues[1]) && Symb != '\n' &&
        Symb != '\t') {
      if (Symb >= 0 && Symb <= 31) {
        printf("^");
        Symb += 64;
      } else if (Symb == 127) {
        printf("^");
        Symb -= 64;
      }
    }

    if (KeyValues[1] && Symb == '\n') {
      printf("$");
    }

    if (Symb == '\n') count = 1;

    printf("%c", Symb);
  }
}