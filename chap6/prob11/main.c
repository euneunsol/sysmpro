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
    else if (argc == 2) {
        if (argv[1][0] == '-') {
            dir = ".";
            option = argv[1][1];
        } else {
            dir = argv[1];
        }
    } else if (argc >= 3) {
        dir = argv[1];
        option = argv[2][1];
    }
    
    if (access(dir, F_OK) == -1) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    if ((dp = opendir(dir)) == NULL) {
        perror("Error opening directory");
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
    printf("%5ld ", st->st_blocks);

    if (option == 'i') {
        printf("%lu ", (unsigned long)st->st_ino);
    }

    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);

    struct passwd *pwd = getpwuid(st->st_uid);
    struct group *grp = getgrgid(st->st_gid);

    if (pwd != NULL)
        printf("%s ", pwd->pw_name);
    else
        printf("%d ", st->st_uid);

    if (grp != NULL)
        printf("%s ", grp->gr_name);
    else
        printf("%d ", st->st_gid);

    printf("%9ld ", st->st_size);

    char *time_str = ctime(&st->st_mtime);
    time_str[strlen(time_str) - 1] = '\0';  
    printf("%s ", time_str);

    if (option == 'p' || option == 'i') {
        if (S_ISDIR(st->st_mode))
            printf("%s/", file);
        else
            printf("%s", file);
    } else if (option == 'Q') {
        if (S_ISDIR(st->st_mode))
            printf("\"%s\"", file);
        else
            printf("%s", file);
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
