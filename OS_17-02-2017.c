/*Scrivere un programma ager in grado di invecchiare file.
Il programma deve poter prendere una lista di file come parametri o nessun parametro, 
nel qual caso invecchieràtutti I file della directory corrente. 
“invecchiare” significa predatare il tempo di ultimo accesso e di modifica di 10giorni.Esempio:
$ ls -l file-rw-r--r-- 
1 renzo renzo    0 Feb 17 09:07 file
$ ./ager file
$ ls -l file-rw-r--r-- 
1 renzo renzo    0 Feb  7 09:07 file

Esercizio 2: Linguaggio C: 10 punti
Completare l’esercizio 1 ponendo una gestione opportuna dei parametri in linea comando 
che preveda di poter modificare solo la data di accesso o quella di modifica,
di definire il tempo di “invecchiamento” e un help.
Si possono inserire altri parametri ritenuti opportuni
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/dir.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *command[200];
    int a = 0;
    int m = 0;
    int modif = 0;
    int argument = argc;
    struct utimbuf time;
    struct stat st;
    char buf[200];
    if (argc > 1)
    {
        if (!strcmp(argv[1], "-help"))
        {
            printf("use -a to change access, -m to change modify \n Use nothing to change both.\nPut a number after -a or -m or as first argument to specify how much to change\n");
            return 0;
        }
        if (!strcmp(argv[1], "-a"))
        {
            a = 1;
            argument--;
        }
        else if (!strcmp(argv[1], "-m"))
        {
            m = 1;
            argument--;
        }
        else if (atoi(argv[1]) > 0)
        {
            modif = atoi(argv[1]);
            a = m = 1;
            argument--;
        }
        else
        {
            a = m = 1;
        }
        if (argc > 2)
        {
            if (atoi(argv[2]) > 0)
            {
                modif = atoi(argv[2]);
                argument--;
            }
        }
    }
    if (argument < 2)
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(".")) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                char *res = realpath(ent->d_name, &buf);
                stat(buf, &st);
                time.actime = st.st_atim.tv_sec - (a * (time_t)(modif * 24 * 60 * 60));
                time.modtime = st.st_mtim.tv_sec - (m * (time_t)(modif * 24 * 60 * 60));
                utime(ent->d_name, &time);
            }
            closedir(dir);
        }
    }
    else
    {
        for (int i = 1; i < argument + 1; i++)
        {
            char *res = realpath(argv[i], &buf);
            stat(buf, &st);
            time.actime = st.st_atim.tv_sec - (a * (time_t)(modif * 24 * 60 * 60));
            time.modtime = st.st_mtim.tv_sec - (m * (time_t)(modif * 24 * 60 * 60));
            utime(argv[i], &time);
        }
    }
    return 0;
}