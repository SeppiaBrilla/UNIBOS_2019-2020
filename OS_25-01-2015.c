/*
Scrivere un programma C di nome filepipe che abbia come unico parametro il pathnae di un file di testo.
Questo file contiene due comandi con I rispettivi parametri, uno per riga.
Il programma deve mettere in esecuzione concorrente I due comandi in modo che l'output del primo venga fornito come input del secondo usando una pipe.
Il programma deve terminare quando entrambi I comandi sono terminati.
Esempio: 
se il file ffff contiene:
    ls -l
    tac
il comando:
filepipe ffff
deve restituire lo stesso output del comando:
    ls -l | tac
*/
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

int main(int argc, char *argv[]){
    FILE * file;
    char command[50][100];
    int j = 0;
    int first = 1;

    if(argc < 2){
        printf("errore!");
        return 1;
    }

    if(!(file = fopen(argv[1],"r"))){
        printf("errore!");
        return 1;
    }

    while(fgets(command[j],sizeof(command[j]),file))
        j++;

    fclose(file);
    printf("%d\n", j);
    int pipefd[j];
    int pid[j];

    if(pipe(pipefd)){
        printf("error!");
        return 1;
    }
    for(int i = 0; i < j; i++){
        pid[i] = fork();
        if(!pid[i] && first){ 
        close(pipefd[i]);
        char name[100];
        char *arguments[20]; 
        int k = 0;
        
        char *ptr = strtok(command[0]," ");
        strcpy(name, "/bin/");
        strcat(name, ptr);
        name[strlen(ptr)+5] = '\0';
        arguments[k] = name;
		ptr = strtok(NULL, " ");
        while(ptr != NULL)
	    {
            k++;
		    arguments[k] = ptr;
            arguments[k][strlen(ptr)-1] = '\0';
            ptr = strtok(NULL, " ");
	    }
        execv(name,arguments);
        }
        if(i == j-1)
            first = 0;
        if(!pid[i] &&  !first)
        {
            close(pipefd[i -1]);

            char name[100];
            char *arguments[2000]; 
            int k = 0;
        
            char *ptr = strtok(command[1]," ");
            strcpy(name, "/bin/");
            strcat(name, ptr);
            name[strlen(ptr)+5] = '\0';
            arguments[k] = name;
		    ptr = strtok(NULL, " ");
            while(ptr != NULL)
	        {
                k++;
		        arguments[k] = ptr;
                arguments[k][strlen(ptr)-1] = '\0';
                ptr = strtok(NULL, " ");
	        }
            k++;
            FILE* output = fdopen(pipefd[0], "r");
            char line[1024];
            char * all[1024];
            while(fgets(line, sizeof(line), output))
            {
                arguments[k] = line;
            }
            fclose(output);
            execv(name,arguments);
        }
    }    

}