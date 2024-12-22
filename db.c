#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    while (1)
    {
        char comanda[100];

        printf("db >> ");
        scanf("%s", comanda);

        pid_t pid = fork();

        if (pid == 0)
        {
            char* argv[] = {"dbxcli-linux-amd64", comanda, NULL};
            char* envp[] = {"PATH=/usr/bin:/bin:/usr/local/bin", NULL};

            execve("/home/bogdan/Desktop/dbxcli/dbxcli-linux-amd64", argv, envp);
            return 1;
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
        }
        
    }

    return 0;
}
