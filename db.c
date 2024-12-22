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
        printf("dropbox >> ");
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
        
        if (i == 1) // daca nu a fost introdus nimic - `a fost apasat enter` nu se intampla nimic 
        {
            continue;
        }

        argv[i] = NULL; // ULtimul argument din argv este NULL
        
        if (strcmp(argv[1], "exit") == 0) 
        {
            for (int j = 1; j < i; j++) 
            {
                free(argv[j]);
            }
            return 0;
        }

        pid_t pid = fork();
        if (pid == 0) // aici copilul va executa comenzile in dbxcli
        {
            char* envp[] = {"PATH=/usr/bin/", NULL};

            if(strcmp(argv[1], "create") != 0)
            {
                if(execve(argv[0], argv, envp) == -1)
                {
                    perror("dropbox >> Fatal error\n");
                    return 1;
                }
            }
        }
        else if (pid > 0) // parinte
        {
            wait(NULL);
        }
        else
        {
            perror("dropbox >> Fatal error\n");
            return 1;
        }

        pid = fork();
        if(pid == 0) // aici copilul va face legatura cu sistemul local de fisiere
        {
            if (strcmp(argv[1], "cp") == 0 || strcmp(argv[1], "ls") == 0 || 
                strcmp(argv[1], "mkdir") == 0 || strcmp(argv[1], "mv") == 0) 
            {
                // mv a.txt test/a.txt
                // mv a.txt test/

                char bin_path[] = "/usr/bin/";
                strcat(bin_path, argv[1]);

                char* local_argv[MAX_INPUT] = { argv[1] };

                int j;
                for (j = 2; argv[j]; j++) 
                {
                    local_argv[j - 1] = argv[j];
                }
                local_argv[j] = NULL;

                if(execve(bin_path, local_argv, NULL) == -1)
                {
                    perror("dropbox >> Fatal error\n");
                    return 1;
                }
            }
            else if (strcmp(argv[1], "create") == 0)
            {
                char bin_path[] = "/usr/bin/touch";

                char* local_argv[MAX_INPUT] = { "touch", argv[2], NULL };

                if(execve(bin_path, local_argv, NULL) == -1)
                {
                    perror("dropbox >> Fatal error\n");
                    return 1;
                }
            }
            else if (strcmp(argv[1], "search") == 0) 
            {
                char bin_path[] = "/usr/bin/find";

                char* file_to_find = argv[3];
                char* path_to_find = argv[2];
                char* local_argv[MAX_INPUT] = { "find", path_to_find, "-name ", file_to_find, NULL };

                if(execve(bin_path, local_argv, NULL) == -1)
                {
                    perror("dropbox >> Fatal error\n");
                    return 1;
                }
            }
        }
        else if(pid > 0)
        {
            wait(NULL);
        }
        else
        {
            perror("dropbox >> Fatal error\n");
            return 1;
        }

        fflush(stdout);
    }

    return 0;
}