#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

    int pid = 0;
    char stringa[50];
    int p1p2[2], fd;
    pipe(p1p2[2]);

    pid = fork();
    if (pid == 0)
    {

        while (1)
        {
            printf("Inserisci delle stringhe, digitare fine per terminare\n");
            scanf("%s", stringa);
            if (strcmp(stringa, "fine") == 0)
            {
                close(p1p2[1]);
                exit(1);
            }

            strcat(stringa, "\n");
            write(p1p2[1], stringa, strlen(stringa));
           // close(1);
            //dup(p1p2[1]);
            //close(p1p2[1]);
            exit(1);
                }
    }
    pid = fork();
    if (pid == 0)
    {
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);
        open(argv[1], O_WRONLY | O_CREAT, 0777);
        execl("/usr/bin/sort" "sort", stringa, fd, NULL);
        exit(1);
        return -1;
    }
    wait(&pid);
}
