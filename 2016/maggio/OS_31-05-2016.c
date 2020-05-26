/*
Scrivere un programma che preso come parametro a linea comando il path di una directory elenchi solamente I fileche hanno un nome che ha come suffisso un numero (es. Prova.10). 
I file devono essere ordinati in ordine numerico.Esempio se la directory test contiene I file 
prova5, giovanni, aaa.1000, bb.2000, ccc.dd.500
l'output del programma deve essere:
    ccc.dd.500
    aaa.1000
    bb.2000
(in quanto 500 numericamente e' minore di 1000, prova5 non si considera: manca il punto prima del numero).
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



struct myfile{
    int ext;
    char name[50];

}typedef myfile_t;


const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int is_dir(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int search_in_dir(char dir[], myfile_t files [], int next){
    DIR *folder;
    struct dirent *entry;
    int is_in = 0;

    folder = opendir(dir);
    if(!folder)
        return -1;
    
    while ((entry = readdir(folder)))
    {
        if(strcmp(entry->d_name,".") != 0 &&strcmp(entry->d_name,"..") != 0){
            char value[30];
            strcpy(value, dir);
            strcat(value,"/");
            strcat(value,entry->d_name);
            if(is_dir(entry->d_name)){
                search_in_dir(value, files, next);
            }else{
                int n;
                if((n = atoi(get_filename_ext(value))) > 0){
                    myfile_t f;
                    strcpy(f.name, value);
                    f.ext = n;
                    files[next] = f;
                    next++;
                }
            }
        }    
    }
    return is_in;
}

int compare( const void* a, const void* b)
{
     myfile_t int_a = * ( (myfile_t*) a );
     myfile_t int_b = * ( (myfile_t*) b );

     if ( int_a.ext == int_b.ext ) return 0;
     else if ( int_a.ext < int_b.ext ) return -1;
     else return 1;
}


int main(int argc, char* argv[]){

    myfile_t to_print[100];
    for(int i = 0; i < 100; i++){
        to_print[i].ext = 0;
    }

    search_in_dir(argv[1], to_print, 0);

    qsort( to_print, 100, sizeof(myfile_t), compare );

    for(int i = 0; i < 100; i++){
        if(to_print[i].ext > 0){
            printf("%s\n", to_print[i].name);

            struct timespec time;
            time.tv_nsec = to_print[i].ext * 10;
            nanosleep(&time, NULL);
            int pid = fork();
            if(pid == 0){
                printf("executing %s\n",to_print[i].name);
                execl(to_print[i].name, to_print[i].name, NULL);
                return 1;
            }
            nanosleep(&time, NULL);
        }
    }

    return 0;
}