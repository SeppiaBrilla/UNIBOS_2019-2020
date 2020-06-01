/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Scrivere la funzione:
    void printgroupdir(const char *dirp, const char *group);
che deve scandire la directory con pathname dirp e stampare  tutti i file (non le directory) che appartengano al gruppo passato come secondo parametro.
Creare i file printgroupdir.c, printgroupdir.h  e un file testpgd.c contenente  un programma  principale che prenda come argv[1] e argv[2] i due parametri della funzione. 
Produrre un Makefile opportuno.
Esempi per provare il funzionamento possono essere:
testpgd /dev tty
testpgd /dev disk
*/

/*
Esercizio 2: Linguaggio C: 10 punti
scrivere la funzione:
    char **groupdir(const char *dirp, const char *group);
che deve scandire la directory con pathname dirp e cercare tutti I file (non le directory) che appartengano al gruppo passato come secondo parametro.
Il valore di ritorno della funzione e’:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Il vettore dei nomi dei file trovati (allocato dinamicamente) con un elemento finale (char *) 0 per indicare la conclusione dell’array 
(in modo simile al vettore argv usato in execve). 
NULL se si sono verificati errori (ad es. La directory non esiste).
(se non vi  sono file del gruppo cercato viene restituito un vettore contenente un solo elemento (char *) 0, nonNULL).

Scrivere inoltre una funzione:
void freestringarray(char **v);
che deallochi un vettore generato dalla groupdir;
Creare I file groupdir.c, groupdir.h e un file testgd.c 
contenente un programma principale che prenda come argv[1]e argv[2] 
i due parametri della funzione e ne stampi il risultato. 
Produrre un Makefile opportuno.
Esempi per provare il funzionamento possono essere:
    testgd /dev tty
    testgd /dev disk

*/
#include "OS_29-07-2016.h"

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void printgroupdir(const char *dirp, const char *group)
{
    struct dirent *dir;
    struct group *grp;
    struct stat st;
    DIR *d;
    int i;
    d = opendir(dirp);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (is_regular_file(dir->d_name))
            {
                stat(dir->d_name, &st);
                grp = getgrgid(st.st_gid);
                if (!strcmp(group, grp->gr_name))
                    printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }
}

char **groupdir(const char *dirp, const char *group)
{
    struct dirent *dir;
    struct group *grp;
    struct stat st;
    int rows = 10;
    char **vector = calloc (rows,sizeof(char*));;
    DIR *d;
    int i = 0;
    d = opendir(dirp);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {                                         
            if (is_regular_file(dir->d_name))
            {
                stat(dir->d_name, &st);
                grp = getgrgid(st.st_gid);
                if (!strcmp(group, grp->gr_name))
                {
                    vector[i] = grp->gr_name;
                    i++;
                }
            }
        }
        closedir(d);
    }
    return vector;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Mancano Argomenti!");
        return 1;
    }
    //printgroupdir(argv[1], argv[2]);
    char ** vector = groupdir(argv[1], argv[2]);
    printf("%s\n", vector[0]);
    return 0;
}
