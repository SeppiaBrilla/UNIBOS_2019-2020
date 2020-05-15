/*Scrivere un programma ager in grado di invecchiare file.
Il programma deve poter prendere una lista di file come parametri o nessun parametro, 
nel qual caso invecchieràtutti I file della directory corrente. 
“invecchiare” significa predatare il tempo di ultimo accesso e di modifica di 10giorni.Esempio:
$ ls -l file-rw-r--r-- 
1 renzo renzo    0 Feb 17 09:07 file
$ ./ager file
$ ls -l file-rw-r--r-- 
1 renzo renzo    0 Feb  7 09:07 file
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char const *argv[])
{
    char *path = argc > 1 ? argv[1] : ".";
    struct utimbuf *time;
    struct stat *st;
    stat(path, st);
    time->actime = st->st_atim.tv_sec - (10 * 24 * 60 * 60);
    time->modtime = st->st_mtim.tv_sec - (10 * 24 * 60 * 60);
    utime(path, time);
    return 0;
}
