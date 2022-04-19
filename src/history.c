#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>



int main (int argc, char* argv[])
{
    if(argv[1]==NULL){
        
        char path[300];

        getcwd(path,300);

        strcat(path,"/history.txt");

        int fd = open(path, O_RDONLY | O_CREAT, 0644); 



        if(fd<0){
            puts("You have no recents movements yet!");
            close(fd);
        }else{

            puts("So far these are your movements:\n\n");
             char buf[4096];
             int lung;

            while(lung=read(fd,buf,sizeof(buf))) //read as much as 4096 in file
            {
                puts("\n");
                write(0,buf,lung); //write on terminal
                puts("\n");
            }
            close(fd);
        }

        
    }else if(argc>1){

        char path[300];

        getcwd(path,300);

        strcat(path,"/history.txt");

        int fd = open(path,O_RDWR|O_APPEND|O_CREAT, 0644);

        if(fd>0){


            char *calculate;
            calculate = (char*)malloc(sizeof(argv) * sizeof(char*));
            
            for(int i = 0; i<argc;i++){
                strcat(calculate, argv[i]);
                //printf("%s, %d",calculate,i);
                strcat(calculate, " ");
            }
            
            write(fd,calculate,strlen(calculate));
            write(fd,"\n",sizeof("\n"));
            close(fd);
        }
        
    }

    
}