/*
Scrivere un programma che mostri il funzionamento del file locking.
In particolare il programma cplk avra’  due argomenti che I pathname di due file. 
Il contenuto del primo file deve essere copiato nel secondo usando la system call sendfile. 
Prima di iniziare la copia occorre usare la system call fcntl per bloccare il file di output (write lock).
Completata la copia occorre chiamare nuovamente la fcntl per sbloccare il file.
Inserire un ritardo (sleep) con valore casuale da 1 a 10 secondi sia prima sia dopo aver sbloccato il file estampe di controllo che indichino quando il file viene bloccato e sbloccato.
In questo modo lanciando piu’ esecuzioni concorrenti con output sullo stesso file deve apparire che l’accesso inscrittura e’ mutualmente esclusivo.
Es. di output:
$  cplk cplk.c 
outlocked                                attende da 1 a 10 
secunlocked                            attende da 1 a 10 sec
$
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <time.h> 

int main (int argc, char* argv[])
{
    if (argc!= 3)
        return 1;

    int fd_dest;
    int fd_source;
    struct flock lock;
    srand(time(0));

    fd_dest = open (argv[1], O_WRONLY);
    fd_source = open(argv[2],O_RDONLY);

    printf ("locking...\n");
    
    memset (&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    
    fcntl (fd_dest, F_SETLKW, &lock);
    int time = 1+rand()%10;
    printf ("locked! Waiting fon %d seconds, then copying file\n",time);
    sleep(time);
    sendfile(fd_dest, fd_source, NULL, 256);

    time = 1+rand()%10;
    printf ("waiting for %d seconds, then unlocking\n",time);
    sleep(time);
    lock.l_type = F_UNLCK;
    fcntl (fd_dest, F_SETLKW, &lock);

    close (fd_dest);
    close (fd_source);
    return 0;

}