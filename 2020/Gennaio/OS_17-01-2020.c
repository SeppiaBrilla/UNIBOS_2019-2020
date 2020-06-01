/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Scrivere un programma searchlink che dati due parametri (nell'ordine un file f ed una directory d)
metta in output l'elenco dei path all'interno dell'albero che ha radice in d che fanno riferimento ad f o come link fisico o come link simbolico.
es: 
searchlink myfile mydir
link a
link d/b
symlink e/s
significa che dir/a e dir/d/b si riferisono a f come link fisici mentre dir/e/s e' un link simbolico che punta ad f.

Esercizio 2: Linguaggio C: 10 punti
Estendere il programma precedente in modo che accetti le seguenti opzioni:
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int is_directory(char const *path)
{
    struct stat path_stat;
    if (strcmp(path, ".."))
    {
        if (strcmp(path, "."))
        {
            stat(path, &path_stat);
            //printf("Folder: %s -> %d \n", path, path_stat.st_mode);
            return S_ISDIR(path_stat.st_mode);
        }
    }
    return 0;
}

void ciclo(char const *file, char const *path, int attribute)
{
    DIR *dp;
    char rlpahtFile[120], rlpathLink[120], buf[120];
    char *newfolder = malloc(sizeof(char) * 120);
    struct stat st, fl;
    struct dirent *entry;
    if ((dp = opendir(path)) == NULL)
    {
        fprintf(stderr, "cannot open directory: %s\n", path);
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dp)) != NULL)
    {
        strcpy(newfolder, path);
        strcat(newfolder, "/");
        strcat(newfolder, entry->d_name);
        lstat(newfolder, &st);
        if (S_ISDIR(st.st_mode))
            if (strcmp(entry->d_name, ".."))
                if (strcmp(entry->d_name, "."))
                    ciclo(file, newfolder, attribute);

        if (S_ISLNK(st.st_mode))
        {
            readlink(newfolder, buf, sizeof(buf));
            realpath(buf, rlpathLink);
            realpath(file, rlpahtFile);
            if (!strcmp(rlpahtFile, rlpathLink))
            {
                if (attribute == 1)
                {
                    link(file, newfolder);
                    unlink(newfolder);
                    link(file, newfolder);
                }
                else
                    printf("symlink %s \n", newfolder);
            }
        }

        if (S_ISREG(st.st_mode))
        {
            stat(newfolder, &st);
            stat(file, &fl);
            if (st.st_ino == fl.st_ino && strcmp(entry->d_name, file) != 0)
            {
                if (attribute == 2)
                {
                    readlink(file, buf, sizeof(buf));
                    realpath(buf, rlpathLink);
                    symlink(file, newfolder);
                    unlink(newfolder);
                    symlink(file, newfolder);
                }
                else
                    printf("link %s\n", entry->d_name);
            }
        }
    }
    free(newfolder);
}

/*
-c copia il file originale al posto di tutti i link
-l trasforma tutti i link in link fisici
-s trasforma tutti i link in link simbolici
*/
int main(int argc, char const *argv[])
{
    int attr;
    if (argc < 2)
    {
        printf("error\n");
        return 1;
    }
    if (strcmp(argv[2], "-c"))
        attr = 0;
    if (strcmp(argv[2], "-l"))
        attr = 1;
    if (strcmp(argv[2], "-s"))
        attr = 2;
    else
        attr = 3;

    ciclo(argv[1], argv[argc - 1], attr);
    return 0;
}