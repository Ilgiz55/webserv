#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*start;

	if (!s1 && !s2)
		return (NULL);
	result = (char *)malloc(((s1 ? strlen(s1) : 0) + (s2 ? strlen(s2) : 0) + 1) * sizeof(char));
	if ((start = result))
	{
		if (s1)
			while (*s1)
				*result++ = *s1++;
		if (s2)
			while (*s2)
				*result++ = *s2++;
		*result = '\0';
	}
	return (start);
}

char* env_pars(char **env, const char *str)
{
    size_t l = strlen(str);
    while (*env)
    {
        if (!strncmp(*env,str,l)) //"QUERY_STRING="
            return strdup(*env + l);
        ++env;
    }
    return strdup("");;
}

int main(int argc, char **argv, char **env)
{
    //php -r 'parse_str($argv[1],$_GET); include("index.php");' 'lesson=1&image=2'
    char *tmp;
    char *arr[5];
    tmp = ft_strjoin("parse_str($argv[1],$_GET); include(\"", argv[1]);
    arr[0] = strdup("/usr/bin/php");
    arr[1] = strdup("-r");
    arr[2] = ft_strjoin(tmp, "\");");
    free(tmp);
    arr[3] = env_pars(env, "QUERY_STRING=");
    arr[4] = NULL;
    int n = execve(arr[0], arr, env);
    int i = 0;
    while (*arr)
        free(arr[i++]);
    return n;
}