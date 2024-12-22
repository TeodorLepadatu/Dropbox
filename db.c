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

        while (p) 
        {
            argv[i] = malloc(strlen(p) + 1);
            strcpy(argv[i], p);
            p = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL;

        for (int a = 0; a < i; a++) {
            printf("%s\n", argv[a]);
        }

        for (int j = 1; j < i; j++) {
            free(argv[j]);
        }
    }

    return 0;
}
