/*
Scrivere un programma che conti I file ordinari e le directory presenti nel sottoalbero della directory passata comeparametro (o della directory corrente se non viene passato alcun parametro).
Ogni file o directory deve venir contato una sola volta anche se e’ presente con diversi nomi a causa dei link fisici.
Ogni altro tipo di file che non sia file ordinario o directory (e.g. socket, named pipe, file speciali, link simbolici)devono essere ignorati.
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>


int is_your_guy(const char *path, int tipo)
{
    struct stat path_stat;
    stat(path, &path_stat);
    if(tipo == 0)
        return S_ISREG(path_stat.st_mode);
    if(tipo == 1)
        return S_ISDIR(path_stat.st_mode);
}

char * getname(char base[],char name[]){
    static char path[30];
    strcpy(path, base);
    strcat(path,"/");
    strcat(path,name);
    return path;    
}

ino_t get_inode(char path[]){

    struct stat file_stat;  
    int ret;  
    ret = stat (path, &file_stat);  
    if (ret < 0) 
       return -1;  

    return file_stat.st_ino; 
}

int search_in_dir(char dir[],ino_t inode,char file_name[]){
    DIR *folder;
    struct dirent *entry;
    int is_in = 0;

    folder = opendir(dir);
    if(!folder)
        return -1;
    
    while ((entry = readdir(folder)))
    {
        if(strcmp(entry->d_name,".") != 0 &&strcmp(entry->d_name,"..") != 0){
            char path[30];
            strcpy(path,getname(dir,entry->d_name));
            if(is_your_guy(path, 1))
                is_in += search_in_dir(path, inode, file_name);
            else if(is_your_guy(path,0)){
                if(get_inode(path) == inode && strcmp(file_name, path)!= 0){
                    return 1;
                }
            }
        }    
    }
    return is_in;
}

int find(int array[], int element, int maxel){
    for(int i = 0; i < maxel; i++){
        if( array[i] == element)
            return i;
    }
    return 0;
}

int scan_dir(char dirname[], int already_counted[],int nname[], int next){
    
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(dirname);
    if(!folder)
        return -1;
    
    while ((entry = readdir(folder)))
    {
        if(strcmp(entry->d_name,".") != 0 &&strcmp(entry->d_name,"..") != 0){
            char path[30];
            strcpy(path,getname(dirname,entry->d_name));
            int inode = get_inode(path);
            if(is_your_guy(path, 1))
                files += scan_dir(path, already_counted, nname, next);
            else if(is_your_guy(path,0)){
                if(search_in_dir(dirname,inode,path) && !find(already_counted, inode, next)){
                    already_counted[next] = inode;
                    nname[next] = 1;
                    next++;
                    files++;
                }else if(!search_in_dir(dirname,inode,path)){
                    already_counted[next] = inode;
                    nname[next] = 1;
                    next++;
                    files++;
                }else{
                    nname[find(already_counted, inode,next)]++;
                }
            }
        }    
    }
    return files;
    
    

}

int main(int argc, char *argv[]){


    char directory[20];
    int files;
    int already_counted[100];
    int nname[100];
    for(int i = 0; i< 100; i++){
        nname[i] = 0;
        already_counted[i] = 0;
    }

    if(argc > 2)
        return 1;
    
    if(argc == 2)
        strcpy(directory,argv[1]);
    else
        strcpy(directory,".");

    if((files = scan_dir(directory, already_counted,nname,0)) > -1){
            printf("numero files : %d\n",files);
            for(int i = 0; i<100; i++){
                if(nname[i] > 0){
                    printf("l'inode %d è linkato da %d files\n",already_counted[i],nname[i]);
                }else{break;}
            }
        }
    else
        printf("errore\n");
    
    return 0;
}