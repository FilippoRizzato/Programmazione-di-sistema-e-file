#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char*argv[]){

    char stringa[1000];
    char conta[1000];
    int contatot = 0;
     int p1p0[2], p0p2[2];
     int pid;
    pipe(p1p0);
     
    while(1){
    printf("Inserisci la stringa");
    scanf("%s", stringa);

    if(strcmp(stringa, "fine") == 0){
        close(p1p0[0]);
        close(p1p0[1]);
        exit(1);
    }
    int pid = fork();
    if(pid == 0){//prima pipe
         close(p1p0[0]);
            close(1);
            dup(p1p0[1]);
            close(p1p0[1]);
            execl("/usr/bin/grep", "grep", stringa, argv[1], NULL);
            return -1;
    }
    pipe(p0p2);
        pid = fork();

        if (pid == 0)//seconda pipe
        {
            close(p1p0[1]);
            close(0);
            dup(p1p0[0]);
            close(p1p0[0]);

            close(p0p2[0]);
            close(1);
            dup(p0p2[1]);
            close(p0p2[1]);
            execl("/usr/bin/wc", "wc", NULL);
            return -1;
        }
        close(p1p0[0]);
        close(p1p0[1]);
        close(p0p2[1]);

        read(p0p2[0], conta, sizeof(conta));
        close(p0p2[0]);
        printf("Il file ha %d '%s' \n", atoi(conta), stringa);
        contatot = contatot + atoi(conta);
    }
    
}
