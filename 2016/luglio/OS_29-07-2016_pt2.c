/*
Scrivere un altro programma rdlk che blocchi il file passato come parametro in lettura (read lock) per un numero disecondi random (da 1 a 10 secondi).
Anche in questo caso inserire stampe di controllo che indichino quando il file viene bloccato e quando vienesbloccato.
Eseguendo molteplici copie di rdlk con cplk dell’esercizio 1 si dovrebbe vedere che I lock rispettano l’invariante deireaders/writers. 
(usare come parametro di rdlk il secondo parametro di cplk).
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
    if (argc!= 2)
        return 1;

    int fd;
    struct flock lock;
    srand(time(0));

    fd = open (argv[1], O_RDONLY);

    printf ("locking...\n");
    
    memset (&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    
    fcntl (fd, F_SETLKW, &lock);
    int time = 1+rand()%10;
    printf ("locked! Waiting fon %d seconds, then unlocking file\n",time);
    sleep(time);
    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);

    close (fd);
    return 0;

}