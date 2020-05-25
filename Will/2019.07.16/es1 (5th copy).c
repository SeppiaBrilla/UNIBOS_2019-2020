// Il file /public/socktest.c è il sorgente di un programma che crea una connessione TCP con la macchina
// locale a porta 2222. E' possibile testarlo con netcat. Se aprite due shell, nella prima digitate:
// nc -l -p 2222
// nella seconda
// socktest
// potete scrivere ora una riga di testo nella seconda finestra e comparira' nella prima, poi scrivendo una
// riga nella prima compare nella seconda ed enrambi i programmi terminano.
// Scopo di questo esercizio è di trasformare/completare il sorgente in modo che diventi una chat fra i
// due terminali... ogni riga scritta nella prima finestra deve comparire nella seconda e viceversa.
// Terminando uno dei due programmi, termina anche l'altro.
// Occorre consegnare due versioni del programma: la prima deve fare uso della system call select, la
// seconda versione deve usare la system call poll.

int main (int argc, char * argv[]){


    return 0
}