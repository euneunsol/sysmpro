#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    int printLineNumbers = 0;
    int fileIndex = 1;

    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        printLineNumbers = 1;
        fileIndex++;
    }

    for (int i = fileIndex; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            continue;
        }

        int c;
        int lineNumber = 1;
        int isLineStart = 1;

        while ((c = getc(fp)) != EOF) {
            if (isLineStart && printLineNumbers) {
                printf("%d: ", lineNumber);
                isLineStart = 0;
            }
            putc(c, stdout);
            if (c == '\n') {
                lineNumber++;
                isLineStart = 1;
            }
        }

        fclose(fp);
    }

    return 0;
}

