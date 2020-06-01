/*
Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Il comando abslink, da implementare, deve sostituire un link simbolico con uno equivalente che sia un riferimento ad un path assoluto.
Ad esempio:  se mylink e' nella directory /home/user e punta a myfile,  'abspath mylink" deve sostituire mylink con un symbolic link a /home/user/myfile.
Hint: considerate l'uso della funzione realpath.
*/
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char rlpath[120], buf[120];
    if (argc < 2)
    {
        printf("Error\n");
        return 1;
    }

    readlink(argv[1], buf, sizeof(buf));
    realpath(buf, rlpath);
    symlink(rlpath, argv[1]);
    unlink(argv[1]);
    symlink(rlpath, argv[1]);

    return 0;
}