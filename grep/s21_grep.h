#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define _GNU_source
#define SIZE 1024
typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int err;
  int SUM;
} KEYS;

char Pattern[10 * SIZE];

void Keys_Expressions(regex_t *regex, int argc, char **argv, KEYS *keys,
                      char *Pattern);
void FileReader(regex_t *regex, char **argv, int argc, KEYS keys);