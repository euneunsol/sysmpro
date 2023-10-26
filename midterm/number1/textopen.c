#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#define MAXLINE 80
static void do_grep(regex_t *pat, FILE *f);

int main(int argc, char *argv[]) {
  regex_t pat;
  int err;
  int i;
  int line = 0;
  char buffer[MAXLINE];
  FILE *fp;

  if (argc < 2) {
    fputs("no pattern\n", stderr);
    exit(1);
  }
  err = regcomp(&pat, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
  if (err != 0) {
    char buf[1024];
    puts(buf);
    exit(1);
  } 
  if ( (fp = fopen(argv[1],"r")) == NULL) {
         fprintf(stderr, "Error Open File\n");
        exit(2);
     }

    while (fgets(buffer, MAXLINE, fp) != NULL) {
        line++;
        if(line < 3) printf("%s", buffer);
    }
    exit(0);
 }

  if (argc == 2) {
    do_grep(&pat, stdin);
  } else {
    for (i = 2; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_grep(&pat, f);
      fclose(f);
    }
  }
  regfree(&pat);
  exit(0);
}

static void do_grep(regex_t *pat, FILE *src) {
  char buf[4096];

  while (fgets(buf, sizeof buf, src)) {
    if (regexec(pat, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    }
  }
}
