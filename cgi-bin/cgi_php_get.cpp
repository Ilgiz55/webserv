#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

char* quary_string(const char **env)
{
    while (*env)
    {
        if (strcmp(*env,"QUERY_STRING="))
            return strdup(*env + 13);
        ++env;
    }
    return strdup("");;
}

int main(int argc, char **argv, char **env)
{
    //php -r 'parse_str($argv[1],$_GET); include("index.php");' 'lesson=1&image=2'
    char *tmp;
    char *arr[4];
    tmp = ft_strjoin("parse_str($argv[1],$_GET); include(\"", argv[1]);
    arr[0] = strdup("/usr/bin/php");
    arr[1] = strdup("-r");
    arr[2] = ft_strjoin(tmp, "\");");
    free(tmp);
    // arr[2] = strdup("parse_str($argv[1],$_GET); include(\"index.php\");");
    arr[3] = quary_string(env);
    // arr[4] = strdup("\n");
    // printf("%s\n", "arr[i]");
    // arr[0] = strdup("/bin/ls");
    // printf("%s\n", "arr[i]");
    // arr[1] = strdup("-l");
    // arr[3] = NULL;
    
    // return execve("php", arr, env);
    int n = execve(arr[0], arr, env);
    // printf("%d\n", n);
    int i = 0;
    while (arr[i])
    {
        printf("%s\n", arr[i]);
        free(arr[i]);
        i++;
    }
    return n;
}