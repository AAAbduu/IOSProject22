#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>



void readManPage(char*path){
    int fd = open(path, O_RDONLY); 

    if(fd<0){

        puts("There is no such command...");
        exit(0);

    }
        
    char buf[4096];
    int lung;

    while(lung=read(fd,buf,sizeof(buf))) //read as much as 4096 in file
    {
        puts("\n\n");
        write(0,buf,lung); //write on terminal
        puts("\n");
    }
    close(fd);
}

int main(int argc,char *argv[]){
    char path [456];
    getcwd(path,sizeof path);

    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/manpages");

    if(argc ==1){

        printf("Use: myman 'command'\nAvailable commands:\n\n");
        printf("history\ninvestigate\ngo\nuse\nkill\n\n");

    }else if(argc==2){

        if(strcmp(argv[1], "history")==0){
            strcat(path,"/history.txt");
            readManPage(path);

        }

       if(strcmp(argv[1], "investigate")==0){
            strcat(path,"/investigate.txt");
            readManPage(path);
        }

        if(strcmp(argv[1], "go")==0){
            strcat(path,"/go.txt");
            readManPage(path);
            
        }

        if(strcmp(argv[1], "use")==0){
            strcat(path,"/use.txt");
            readManPage(path);
        }
        if(strcmp(argv[1], "inventory")==0){
            strcat(path,"/inventory.txt");
            readManPage(path);
        }
        if(strcmp(argv[1], "take")==0){
            strcat(path,"/take.txt");
            readManPage(path);
        }

    }


}

