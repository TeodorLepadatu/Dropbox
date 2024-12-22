#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 200
#define MAX_ARGS 100

int main() 
{
    while (1) 
    {
        char* argv[MAX_ARGS];
        char comanda[MAX_INPUT];

        argv[0] = "./dbxcli-linux-amd64"; 
        printf(">> ");
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
        if (argv[1] == '\0') 
        {
            continue;
        }
        argv[i] = NULL;
        if (argv[1] && strcmp(argv[1], "exit") == 0) 
        {
            for (int j = 1; j < i; j++) {
                free(argv[j]);
            }
            break;
        }

        pid_t pid = fork();
        if (pid == 0) 
        {
            char* envp[] = {"PATH=/usr/bin:/bin:/usr/local/bin", NULL};

            execve(argv[0], argv, envp);

            perror("execve (dbxcli)");
            return 1;
        }
        else if (pid > 0) 
        {
            int status;
            waitpid(pid, &status, 0); 
        }

        pid_t local_pid = fork();
        if (local_pid == 0) 
        {
            if (strcmp(argv[1], "cp") == 0 || strcmp(argv[1], "ls") == 0 || 
                strcmp(argv[1], "mkdir") == 0 || strcmp(argv[1], "mv") == 0) 
            {
                char local_command[MAX_INPUT] = {0};
                for (int j = 1; argv[j]; j++) {
                    strcat(local_command, argv[j]);
                    strcat(local_command, " ");
                }

                execl("/bin/sh", "/bin/sh", "-c", local_command, (char*)NULL);
                perror("execve (local command)");
                return 1;
            }
            else if (strcmp(argv[1], "search") == 0) 
            {
                char find_command[MAX_INPUT] = "find ";
                if (argv[2]) 
                {
                    strcat(find_command, argv[2]); 
                } 
                else 
                {
                    strcat(find_command, "."); 
                }

                strcat(find_command, " -name \"");
                if (argv[3]) 
                {
                    strcat(find_command, argv[3]); 
                } 
                else 
                {
                    strcat(find_command, "*"); 
                }
                strcat(find_command, "\"");

                execl("/bin/sh", "/bin/sh", "-c", find_command, (char*)NULL);
                perror("execve (local search)");
                return 1;
            }
            return 0;
        }
        else if (local_pid > 0) 
        {
            int status;
            waitpid(local_pid, &status, 0); 
        }

        for (int j = 1; j < i; j++) {
            free(argv[j]);
        }
    }

    return 0;
}
