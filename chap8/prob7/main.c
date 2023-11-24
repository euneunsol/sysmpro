#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    int option;
    char *env_var_name = NULL;
    extern char **environ;

    while ((option = getopt(argc, argv, "e:ugiip")) != -1) {
        switch (option) {
            case 'e':
                env_var_name = optarg;
                if (env_var_name != NULL) {
                    char *env_var_value = getenv(env_var_name);
                    if (env_var_value != NULL) {
                        printf("%s=%s\n", env_var_name, env_var_value);
                    } else {
                        printf("error");
                    }
                } else {
		    printf("error2");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'u':
                printf("My Realistic User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
                printf("My Valid User ID: %d(%s)\n", geteuid(), getpwuid(getuid())->pw_name);
                break;
            case 'g':
                printf("My Realistic Group ID: %d(%s)\n", getgid(), getpwuid(getuid())->pw_name);
                printf("My Valid ID: %d(%s)\n", getegid(), getpwuid(getuid())->pw_name);
                break;
            case 'i':
                printf("my process number: [%d]\n", getpid());
                break;
            case 'p':
                printf("my parent's process number: [%d]\n", getppid());
                break;
            default:
                
                    for (char **env = environ; *env != NULL; ++env) {
                        printf("%s\n", *env);
			}
                
        }
    }

    return 0;
}

