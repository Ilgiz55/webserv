#include <stdio.h>
#include <stdlib.h>
// # include <dirent.h>
// # include <sys/stat.h>


int main(int argc, char **argv, char **env)
{
    extern char **environ;

	setenv("CONTENT_TYPE", "text/html", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    while (*environ)
    {
        printf("%s\n", *environ);
        ++environ;
    }
    // printf("%s\n", "!!!!!!!!!");
    // while (*env)
    // {
    //     printf("%s\n", *env);
    //     ++env;
    // }
    return 0;
}