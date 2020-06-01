/*
Esercizio 2: Linguaggio C: 10 punti
Scrivere il comando absls che mostri per ogni file della directory passata
come parametro il path completo di ogni file 
(mostrando al posto dei link simbolici il path completo dei file puntati).
*/
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int is_symlink(const char *path)
{
    struct stat path_stat;
    lstat(path, &path_stat);
    return S_ISLNK(path_stat.st_mode);
}

int main(int argc, char const *argv[])
{
    DIR *dp;
    char rlpath[120], buf[120];
    struct stat st;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(argv[1])) == NULL)
    {
        fprintf(stderr, "cannot open directory: %s\n", argv[1]);
        return 1;
    }
    while ((entry = readdir(dp)) != NULL)
    {

        if (is_symlink(entry->d_name))
        {
            readlink(argv[1], buf, sizeof(buf));
            realpath(buf, rlpath);
            symlink(rlpath, argv[1]);
            unlink(argv[1]);
            symlink(rlpath, argv[1]);
        }
        else
        {
            realpath(entry->d_name, buf);
        }
        printf("Name:%s -> Realpath:%s\n", entry->d_name, buf);
    }

    return 0;
}