#include <stdio.h>
#include <string.h>

int main() {
    char strings[5][100]; 
    int i = 0;
    while (i < 5) {
        fgets(strings[i], sizeof(strings[i]), stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0'; 
        i++;
    }

    for (i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (strlen(strings[i]) < strlen(strings[j])) {
                char temp[100];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }
    }

    for (i = 0; i < 5; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}

