/*
IL programma weakripto deve “criptare” un file. 
weakripto filenamesostituisce il contenuto del file indicato come parametri (non fa copie! Il file deve essere riscritto sul posto)e ogni byte deve avere 
I bit scambiati rispetto al byte corrispondente nel contenuto originale.S
e   il   primo   byte   contiene   il   carattere   ascii  A  (binario   0x41   binario   01000001)   il   primo   byte   del   file   dopo   latrasformazione sara'
0x82 (10000010). 
La lettera ascii B (0x42) rimane invariata.Si chiede di non usare file temporanei e di non caricare l'intero file in memoria.
Come prova di funzionamento, eseguendo due volte lo stesso comando il contenuto del file deve tornare quellooriginale.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str, int size){


    for(int i = 0; i < size; i++){
        
        if(str[i] != '\n' && str[i] != '\0')
            str[i] = ~str[i];
    }
}

int main(int argc, char * argv[]){

    if(argc != 2){
        printf("too few or too much argument!\n");
        return 1;
    }
    

    FILE * f = fopen(argv[1],"r+");
    if(!f){
        printf("error opening file!\n");
        return 1;
    }

    char line[100];
    fpos_t postw, postr;
    fgetpos(f, &postw);
    while (fgets(line,100,f))
    {
        fgetpos(f, &postr);
        fsetpos(f, &postw);
        reverse(line, 100);
        fputs( line, f );
        fsetpos(f, &postr);
        fgetpos(f, &postw);
    }
    return 0;
}