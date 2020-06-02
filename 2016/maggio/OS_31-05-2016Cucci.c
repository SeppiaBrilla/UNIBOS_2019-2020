/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Scrivere un programma che preso come parametro a linea comando il path di una directory 
elenchi solamente I file che hanno un nome che ha come suffisso un numero (es. Prova.10). 
I file devono essere ordinati in ordine numerico.
Esempio se la directory test contiene I file prova5, giovanni, aaa.1000, bb.2000, ccc.dd.500
l'output del programma deve essere:
    ccc.dd.500
    aaa.1000
    bb.2000
(in quanto 500 numericamente e' minore di 1000, prova5 non si considera: manca il punto prima del numero).

Esercizio 2: Linguaggio C: 10 punti 
completamento es 1.
Come nell'esercizio 1 occorre cercare in una directory (passata come parametro) 
I file che hanno come suffisso un numero. 
Nell'esercizio 2 I file sono eseguibili e il numero indica il numero di millisecondi 
da attendere a partire dall' attivazione del programma prima di attivarli.
Nell'esempio dell'esercizio precedente occorre aspettare mezzo secondo e lanciare ccc.dd.500, 
poi a 1 secondo dall'attivazione (cioe' dopo approssimativamente ulteriori 0.5 secondi) 
si lancia aaa.1000 e allo scadere del secondo secondo bbb.2000.
I file eseguibili nella directory vengono eseguiti in background 
(non si attende la fine dell'esecuzione percontinuare). 
Quindi se due file hanno lo stesso prefisso numerico vengono eseguiti in modo concorrente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


int indice = 0;

struct myfile
{
    int suffix;
    char nome[100];
} typedef myfile_t;

const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

int compare(const void *a, const void *b)
{
    myfile_t int_a = *((myfile_t *)a);
    myfile_t int_b = *((myfile_t *)b);
    if (int_a.suffix == int_b.suffix)
        return 0;
    else if (int_a.suffix < int_b.suffix)
        return -1;
    else
        return 1;
}

int is_directory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int searchDirectory(char const *path, myfile_t files[])
{
    DIR *directory;
    struct dirent *entry;
    char riga[50];

    if (!(directory = opendir(path)))
        return 1;

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            strcpy(riga, path);
            strcat(riga, "/");
            strcat(riga, entry->d_name);
            if (is_directory(entry->d_name))
                searchDirectory(riga, files);
            if (atoi(get_filename_ext(entry->d_name)) > 0)
            {
                myfile_t f;
                f.suffix = atoi(get_filename_ext(entry->d_name));
                strcpy(f.nome, entry->d_name);
                files[indice] = f;
                indice++;
            }
        }
    }
    qsort(files, indice, sizeof(files[0]), compare);

    /*for (int j = 0; j <= i; j++)
    {
        printf("%s\n", files[j].nome);
    }*/
    return 0;
}

void executeFile(myfile_t files[]){
    int j = 0;
    while(j < indice){
        printf("%s\n",files[j].nome);
        printf("%d\n",files[j].suffix);
        struct timespec time;
        time.tv_nsec = files[j].suffix * 10;
        usleep(files[j].suffix);   
        j++;
    }
}

int main(int argc, char const *argv[])
{
    FILE *fp;

    myfile_t files[60];

    if (argc < 2)
    {
        printf("Error\n");
        return 1;
    }

    searchDirectory(argv[1], files);

    executeFile(files);

    return 0;
}

//void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))