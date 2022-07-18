#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

char	*ft_strjoin(char const *s1, char const *s2, char const *s3, char const *s4, char const *s5)
{
	char	*result;
	char	*start;
    size_t  l;

	if (!s1 && !s2 && !s3 && !s4 && !s5)
		return (NULL);
    l = (s1 ? strlen(s1) : 0) + (s2 ? strlen(s2) : 0) + (s3 ? strlen(s3) : 0) + (s4 ? strlen(s4) : 0) + (s5 ? strlen(s5) : 0);
	result = (char *)malloc((l + 1) * sizeof(char));
	if ((start = result))
	{
		if (s1)
			while (*s1)
				*result++ = *s1++;
		if (s2)
			while (*s2)
				*result++ = *s2++;
		if (s3)
			while (*s3)
				*result++ = *s3++;
		if (s4)
			while (*s4)
				*result++ = *s4++;
		if (s5)
			while (*s5)
				*result++ = *s5++;
		*result = '\0';
	}
	return (start);
}

char* env_pars(char **env, const char *str)
{
    size_t l = strlen(str);
    while (*env)
    {
        if (!strncmp(*env,str,l))
            return strdup(*env + l);
        ++env;
    }
    return strdup("");;
}

int main(int argc, char **argv, char **env)
{
    //php -r 'parse_str($argv[1],$_GET); include("index.php");' 'lesson=1&image=2'
    char *method;
    std::string str;
    method = env_pars(env, "REQUEST_METHOD=");
    char *arr[5];
    arr[0] = strdup("/usr/bin/php");
    arr[1] = strdup("-r");
    arr[2] = ft_strjoin("parse_str($argv[1],$_", method, "); include(\"", argv[1], "\");");
    if (!strcmp(method, "POST"))
    {
        std::cin >> str;
        arr[3] = strdup(str.c_str());
    }
    else if (!strcmp(method, "GET"))
        arr[3] = env_pars(env, "QUERY_STRING=");
    arr[4] = NULL;
    free(method);
    int n = execve(arr[0], arr, env);
    int i = 0;
    while (*arr)
        free(arr[i++]);
    return n;
}