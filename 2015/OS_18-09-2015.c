/*

La directory /proc contiene un file system virtuale utile per consultare o modificare strutture dati del kernel.
All'interno di tale directory c'e' una sotto directory per ogni processo attivo nel sistema (riconoscibile perche' il nome
della sotto directory e' il numero del processo).
Scrivere un programma che stampi il numero dei processi attivi e rimanga in attesa controllando ogni secondo quanti siano. 
In caso di variazione del numero dei processi stampa il nuovo numero.
Es:
$ count
proc
230
232
230


countprocuser  e' una estensione del programma dell'esercizio 1.
Se viene indicato come parametro il nome di un utente deve contare non gia' tutti I processi ma solo quellidell'utente specificato.
*/

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <pwd.h>


int getuser(char *process){
    char file[50];
    FILE * fp;
    char line[30];
    int uid = 0;
    strcpy(file,"/proc/");
    strcat(file, process);
    strcat(file,"/status");
    if((fp = fopen(file, "r")) == NULL){
        return 1;
    }
    while(fgets(line,sizeof(line),fp)){
        if (strstr(line, "Uid:") != NULL)
            break;
    }
    fclose(fp);
    for(int i = 10; i < 14; i++)
        uid += atoi(&line[i]);
    return uid;
}

int main(int argc, char *argv[]){

    DIR * directory;
    struct dirent *entry;
    struct stat statbuf;
    int nproc;
    int counter = 0;
    int changes = -1;
    int user;

    if(argc < 2)
        return 1;

    struct passwd *pwd = calloc(1, sizeof(struct passwd));
    if(pwd == NULL)
    {
        fprintf(stderr, "Failed to allocate struct passwd for getpwnam_r.\n");
        exit(1);
    }
    size_t buffer_len = sysconf(_SC_GETPW_R_SIZE_MAX) * sizeof(char);
    char *buffer = malloc(buffer_len);
    if(buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate buffer for getpwnam_r.\n");
        exit(2);
    }
    getpwnam_r(argv[1], pwd, buffer, buffer_len, &pwd);
    if(pwd == NULL)
    {
        fprintf(stderr, "getpwnam_r failed to find requested entry.\n");
        exit(3);
    }

    user = pwd->pw_uid;
    if(!(directory = opendir("/proc")))
        return 1;
    while(1){
        while((entry = readdir(directory)) != NULL){
            lstat(entry->d_name,&statbuf);
            if(S_ISDIR(statbuf.st_mode)){
                if(getuser(entry->d_name) == user)
                    counter++; 
            }
        }
        if(counter != nproc){
            nproc = counter;
            changes++;
            printf("nproc = %d    changed %d times\n", nproc, changes);
        }
        rewinddir(directory);
        counter = 0;
    }
    return 0;
}