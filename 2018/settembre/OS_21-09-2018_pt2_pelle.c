/*
Dato un estratto di un file di log come questo:

Sep 20 19:58:32 eipi ntpd[2051]: Listen normally on 99 eth0 [fe80::8456:a70]:123
Sep 20 19:58:32 eipi ntpd[2051]: new interface(s) found: waking up resolver
Sep 20 19:58:34 eipi ntpd[2051]: Soliciting pool server 151.3.106.211
Sep 20 19:58:35 eipi ntpd[2051]: Soliciting pool server 94.177.187.22
Sep 20 19:58:48 eipi ntpd[2051]: Soliciting pool server 80.211.155.206
Sep 20 19:58:49 eipi ntpd[2051]: Soliciting pool server 212.45.144.206

Scrivere un programma che lo mostri alla stessa velocita' allla quale e' stato generato.
In questo caso dovrebbe scrivere le prime dur righe, attendere 2 secondi, mostrare la terza, 
dopo un secondo la quarta quindi dopo una attesa di 13 secondi la quinta e la sesta dopo un ulteriore secondo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getmounth(char *str){
    if(strcmp(str, "Gen")==0)
        return 0;
    if(strcmp(str, "Feb")==0)
        return 1 * 28;
    if(strcmp(str,"Mar")==0)
        return 2 * 31;
    if(strcmp(str,"Apr")==0)
        return 3 * 30;
    if(strcmp(str,"May")==0)
        return 4 * 31;
    if(strcmp(str, "Jun")==0)
        return 5 * 30;
    if(strcmp(str, "Jul")==0)
        return 6 * 31;
    if(strcmp(str, "Aug")==0)
        return 7 * 31;
    if(strcmp(str, "Sep")==0)
        return 8 * 30;
    if(strcmp(str, "Oct")==0)
        return 9 * 31;
    if(strcmp(str, "Nov")==0)
        return 10 * 30;
    if(strcmp(str, "Dic")==0)
        return 11 * 31;
    return 0;
}

int main(int argc, char * argv[]){

    if(argc != 2){
        printf("error, too much or too few arguments");
        return 1;
    }

    FILE *f;
    char line[100];
    char tp[100];
    int mounth, day, hour, min, seconds;
    int prevmounth = 0, prevday = 0, prevhour = 0, prevmin = 0, prevseconds = 0;

    f = fopen(argv[1],"r");
    if(!f){
        printf("error while opening the file %s",argv[1]);
        return 1;
    }
    while(fgets(line,100,f)){
        strcpy(tp,line);
        mounth = getmounth(strtok(line, " "));
        day = atoi(strtok(NULL, " "));
        char *to_div;
        to_div = strtok(NULL, " ");
        hour = atoi(strtok(to_div,":"));
        min = atoi(strtok(NULL,":"));
        seconds = atoi(strtok(NULL,":"));
        if(!(prevday == 0 && prevhour == 0 && prevmin == 0 && prevmounth == 0 && prevseconds == 0)){
            sleep(seconds - prevseconds + ((min - prevmin) * 60) + ((hour - prevhour) * 60 * 60) + ((day -prevday) * 24 * 60 * 60 ) + ((mounth -prevmounth) * 24 * 60 * 60));
        }
        printf("%s\n",tp);
        prevday = day;
        prevhour = hour;
        prevmin = min;
        if(mounth != 11 * 31)
            prevmounth = mounth;
        else
            prevmounth = -(31 - day); 
        prevseconds = seconds;

    }

    return 0;
}