#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

void calculatePath(){
    
    chdir("../gameTree");

}


int main (int argc, char* argv[])
{
    if(argv[1]==NULL){
        
        calculatePath();

        char path[300];

        getcwd(path,300);

        strcat(path,"/history.txt");

        int fd = open(path, O_RDONLY | O_CREAT, 0644); 



        if(fd<0){
            puts("You have no recents movements yet!");
            close(fd);
            //exit(1);
        }else{

            puts("So far these are your movements:\n\n");
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

        
    }else if(argc>1){

        calculatePath();

        char path[300];

        getcwd(path,300);

        strcat(path,"/history");

        int fd = open(path,O_RDWR|O_APPEND|O_CREAT, 0644);

        //printf("%d",fd);

        if(fd>0){
            puts("I reached here");
            printf("%s",argv);
            //char calculateCommand [128];
            //strcat(calculateCommand,argv);
            //int lung = sizeof(calculateCommand);
            write(fd,*argv,sizeof(argv));
            close(fd);
        }
        
    }

    
}

