/*
scrivere un programma para per lanciare parallelamente comandi

para sleep 20 // ls -l // ps // sleep 3

deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
*/
// #include <string.h>
// #include <stdio.h>
// #include <unistd.h>

// int main(int argc, char * argv[]){

//     char commands[10][50];
//     int commandindex=0;
//     int status;

//     for(int i = 0; i< 10; i++){
//         strcpy(commands[i], "");
//     }

//     for(int i = 1; i< argc; i++){
//         if(strcmp(argv[i], "//")==0){
//             commandindex++;
//         }else{
//             strcat(commands[commandindex],argv[i]);
//             strcat(commands[commandindex], " ");
//         }
//     }    
    
//     int pid[commandindex];

//     for(int i = 0; i<= commandindex; i++){
//         pid[i] = fork();
//         if(pid[i] == 0){
//             system(commands[i]);
//             printf("processo %d completato\n", getpid());
//             return 0;
//         }else{
//             printf("processo %d lanciato\n", pid[i]);
//         }
//     }

//     while (wait(&status) > 0);
//     printf("finito!\n");
//     return 0;
// }



//parte 2
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct command{
    char name[20];
    char * param[20];
    int nparam;
}typedef command_t;

int main(int argc, char * argv[]){
    command_t commands[10];
    int commandindex=0;
    int status;
    int maxcommands = 0;
    int current = 0;
    char buff[60];

    if(!(maxcommands = atoi(argv[1]))){
        printf("error");
        return 1;
    }
    for(int i = 0; i< 10; i++){
        commands[i].nparam = 0;
    }

    for(int i = 2; i< argc; i++){
        if(strcmp(argv[i], "//")==0){
            commands[commandindex].param[commands[commandindex].nparam] = NULL;
            commandindex++;
        }else{
            if(commands[commandindex].nparam == 0){
                strcpy(commands[commandindex].name,"/bin/");
                strcat(commands[commandindex].name, argv[i]);
                commands[commandindex].param[commands[commandindex].nparam] = commands[commandindex].name;
                commands[commandindex].nparam++;
            }else
            {
                commands[commandindex].param[commands[commandindex].nparam] = argv[i];
                commands[commandindex].nparam++;
            }
            
        }
    }
    commands[commandindex].param[commands[commandindex].nparam] = NULL;
    int pid[commandindex];
    /*for(int i = 0; i <= commandindex; i++){
        printf("Nome: %d : %s \n",i, commands[i].name);
        for(int j = 0; j < commands[i].nparam; j++){
            printf("%d : %s\n", j, commands[i].param[j]);
        }
    }*/
    
    for(int i = 0; i<= commandindex; i++){
        if(current==maxcommands){
            wait(&status);
            current --;
        }
        pid[i] = fork();
        if(pid[i] == 0){
            execv(commands[i].name, commands[i].param);
        }else{
            current++;
            printf("processo %d lanciato\n numero processi = %d\n", pid[i], current);
        }
    }

    while (wait(&status) > 0);

    printf("finito!\n");
    return 0;
}

/*
Cucci Test
Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Scrivere un programma para per lanciare parallelamente comandi:
para sleep 20 // ls -l // ps // sleep 3
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t wpid;
    char commands[10][50], *comando[50], *riga;
    int j = 0, x = 0, status, current = 0, maxcommands;

    if (!(maxcommands = atoi(argv[1])))
    {
        printf("error");
        return 1;
    }

    if (argc < 2)
    {
        printf("Error\n");
        return 1;
    }

    for (int i = 0; i < 10; i++)
        strcpy(commands[i], "");

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "//") == 0)
            j++;
        else
        {
            strcat(commands[j], argv[i]);
            strcat(commands[j], " ");
        }
    }

    pid_t children[j];

    for (int i = 0; i <= j; i++)
    {
        if (current >= maxcommands)
        {
            wait(&status);
            current--;
        }

        current++;
        strcpy(riga, "");
        x = 0;
        strcpy(comando, "");
        comando[x] = strtok(commands[i], " ");

        while (comando[x] != NULL)
        {
            x++;
            comando[x] = strtok(NULL, " ");
        }

        strcat(riga, "/bin/");
        strcat(riga, comando[0]);

        children[i] = fork();
        if (children[i] == 0)
        {
            execv(riga, comando);
            return 0;
        }
    }

    while (wpid = wait(&status) > 0)
        ;
    return 0;
}*/
