#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    char savedText[10][100];
    int fileCount = 0;
    int totalLines = 0;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            continue;
        }

        char buf;
        int row = 0;

        while (fread(&buf, 1, 1, fp) > 0) {
            if (buf == '\n') {
                savedText[fileCount][row] = '\0';
                row = 0;
                fileCount++;
            } else {
                savedText[fileCount][row] = buf;
                row++;
            }
        }

        fclose(fp);
    }

    printf("file read success\n");
    totalLines = fileCount;

    printf("Total line: %d\n", totalLines);
    printf("You can choose 1 ~ %d Line\n", totalLines);
    printf("Pls 'Enter' the line to select: ");

    int lineNumber, startLine, endLine;
    char input[10];
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < totalLines; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (sscanf(input, "%d-%d", &startLine, &endLine) == 2) {
        if (startLine >= 1 && endLine >= startLine && endLine <= totalLines) {
            for (int i = startLine; i <= endLine; i++) {
                printf("%s\n", savedText[i - 1]);
            }
        } else {
            printf("error\n");
        }
    } else if (sscanf(input, "%d,%d", &startLine, &endLine) == 2) {
        if (startLine >= 1 && startLine <= totalLines && endLine >= 1 && endLine <= totalLines) {
            printf("%s\n", savedText[startLine - 1]);
            printf("%s\n", savedText[endLine - 1]);
        } else {
            printf("error\n");
        }
    } else if (sscanf(input, "%d", &lineNumber) == 1) {
        if (lineNumber >= 1 && lineNumber <= totalLines) {
            printf("%s\n", savedText[lineNumber - 1]);
        } else {
            printf("error\n");
        }
    } else {
        printf("error\n");
    }

    return 0;
}

