#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, char);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    char option = '\0';

    if (argc == 1)
        dir = ".";
    else {
        dir = argv[1];
        if (argc > 2)
            option = argv[2][1];
    }

    if (access(dir, F_OK) == -1) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st, option);
    }

    closedir(dp);
    exit(EXIT_SUCCESS);
}

void printStat(char *pathname, char *file, struct stat *st, char option) {
    printf("%5ld ", st->st_blocks);  // 수정된 부분
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,
           getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);

    if (option == 'p') {
        if (S_ISDIR(st->st_mode))
            printf("%s/", file);
        else
            printf("%s", file);
    } else if (option == 'i') {
        printf("%lu %s", (unsigned long)st->st_ino, file);
    } else if (option == 'Q') {
        printf("\"%s\"", file);
    } else {
        printf("%s", file);
    }

    printf("\n");
}

char type(mode_t mode) {
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';

    return '?';
}

char *perm(mode_t mode) {
    static char perms[11];
    strcpy(perms, "----------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}

