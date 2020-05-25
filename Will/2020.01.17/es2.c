// Estendere il programma precedente in modo che accetti le seguenti opzioni:
// -c copia il file originale al posto di tutti i link
// -l trasforma tutti i link in link fisici
// -s trasforma tutti i link in link simbolici

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h> 

#define ATTR_COPY 1
#define ATTR_TOPH 2
#define ATTR_TOSY 3

void do_attr(char * file, char * linkpath, int attr){
    FILE * from, * to;
    char c;
    remove(linkpath);
    switch (attr)
    {
        case ATTR_COPY:
            from=fopen(file,"r");
            to=fopen(linkpath,"w");
            while((c=fgetc(from))!=EOF){
                //putchar(c);
                fputc(c, to);
            }
            fclose(from);
            fclose(to);
            break;
        case ATTR_TOPH:
            link(file,linkpath);
            break;
        case ATTR_TOSY:
            symlink(file,linkpath);
            break;
    }
}

void searching(ino_t *inode, char *filename, char *pathfrom, int attr){

    struct dirent *ent;
    struct stat st;
    DIR *dir;
    char * path=malloc(sizeof(char)*1000);

    if ((dir = opendir(pathfrom)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            strcpy(path,pathfrom);
            strcat(path, "/");
            strcat(path, ent->d_name);
            lstat(path,&st);
            if(S_ISDIR(st.st_mode)){
                if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
                    searching(inode, filename, path, attr);
            }
            else if(S_ISLNK(st.st_mode)){
                stat(path,&st);
                if(st.st_ino==*inode){
                    //printf("symlink %s\n",path);
                    if(attr==ATTR_TOPH || attr==ATTR_COPY)
                        do_attr(realpath(filename,NULL),path,attr);
                }
            }
            else if(S_ISREG(st.st_mode)){
                if(st.st_ino==*inode && strcmp(realpath(filename,NULL),realpath(path,NULL))!=0){
                    //printf("link %s\n",path);
                    if(attr==ATTR_TOSY || attr==ATTR_COPY)
                        do_attr(realpath(filename,NULL),realpath(path,NULL),attr);
                }
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
    free(path);
}

int main (int argc, char * argv[]){
    struct stat st;
    int attr = 0;
    stat(argv[1], &st);
    for(int i=2; i<argc-1; i++){
        if(strcmp("-c",argv[i])==0)
            attr=ATTR_COPY;
        if(strcmp("-l",argv[i])==0)
            attr=ATTR_TOPH;
        if(strcmp("-s",argv[i])==0)
            attr=ATTR_TOSY;
    }
    searching(&(st.st_ino), argv[1], argv[argc-1], attr);
}