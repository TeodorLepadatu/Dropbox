#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT 200
#define MAX_ARGS 100

int main() 
{
    while (1) 
    {
        char* argv[MAX_ARGS];
        char comanda[MAX_INPUT];

        argv[0] = "dbxcli-linux-amd64";

        fgets(comanda, MAX_INPUT, stdin);

        comanda[strcspn(comanda, "\n")] = '\0';

        char* p = strtok(comanda, " ");
        int i = 1;
        /*
            dbxcli cp [flags] <source> [more sources] <target>
            dbxcli ls [flags] [<path>]
            dbxcli mkdir [flags] <directory>
            dbxcli mv [flags] <source> <target>
            dbxcli search [flags] <query> [path-scope] =>>> in linux este cu find
        */
        while (p) 
        {
            argv[i] = malloc(strlen(p) + 1);
            strcpy(argv[i], p);
            p = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL;

        pid_t pid = fork();
        if (pid == 0)
        {
            char* envp[] = {"PATH=/usr/bin:/bin:/usr/local/bin", NULL};
            execve("./dbxcli-linux-amd64", argv, envp);
            return 1;
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
        }

        for (int j = 1; j < i; j++) {
            free(argv[j]);
        }
    }

    return 0;
}
