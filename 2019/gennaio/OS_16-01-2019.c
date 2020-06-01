/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Usando  inotify creare il  programma  neverm che controlli  una  directory. 
Ogni volta che viene cancellato un file nella  directory sotto osservazione crei un file vuoto di uguale nome. 
Per esempio eseguendo:
    neverm dir 
dove dir e' una directory contenente i file a, b, c, anche a seguito dei comandi 'rm dir/a' e 'rm dir/b', dir deve contenere sempre i file a, b e c, a e b saranno file vuoti.
*/
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    char buf[4096];
    char address[50];
    struct inotify_event *intf;
    unsigned int init;
    ssize_t len;

    if (argc < 1)
    {
        printf("Error! \n");
        return 1;
    }

    init = inotify_init();

    if (inotify_add_watch(init, argv[1], IN_DELETE | IN_DELETE_SELF) < 0)
    {
        printf("Error\n");
        return 0;
    }

    while (1)
    {
        read(init, buf, sizeof buf);
        intf = (struct inotify_event *) &buf[0];
        strcpy(address, argv[1]);
        strcat(address, "/");
        strcat(address,intf->name);
        FILE * file = fopen(address, "w");
        fclose(file);
    }
}
*/

/*
Esercizio 2: Linguaggio C: 10 punti
modificare neverm per fare in modo che neverm ripristini anche il contenuto dei file a seguito della cancellazione (il modo è lasciato alla creatività del candidato)
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    char buffer[5][100];
    char buf[4096];
    char address[50];
    struct inotify_event *intf;
    unsigned int init;
    ssize_t len;
    DIR* FD; 
    struct dirent* in_file;

    if (argc < 1)
    {
        printf("Error! \n");
        return 1;
    }
    if (NULL == (FD = opendir (argv[1]))){

        return 1;
    }
    int x = 0;
    for(int k = 0; k < 5; k ++){
        strcpy(buffer[k],"");
    }
    while ((in_file = readdir(FD))) 
    {
        printf("%s\n",in_file->d_name);
        char c;
        strcpy(address, argv[1]);
        strcat(address, "/");
        strcat(address,in_file->d_name);
        FILE *fp =fopen(address,"r");
        while ((c = fgetc(fp)) != EOF){
            printf("qua\n");
            char stringa[2] = {c , 0};
            strcat(buffer[x], stringa);
        }
        x++;

    }
    printf("%d\n",x);
    for(int k = 0; k< x; k++){
        printf("%s \n",buffer[k]);
    }
    init = inotify_init();

    if (inotify_add_watch(init, argv[1], IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_CREATE) < 0)
    {
        printf("Error\n");
        return 0;
    }

    while (1)
    {
        read(init, buf, sizeof buf);
        intf = (struct inotify_event *) &buf[0];
        strcpy(address, argv[1]);
        strcat(address, "/");
        strcat(address,intf->name);
        FILE * file = fopen(address, "w");
        fclose(file);
    }
}