#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include "investigate.h"


#ifdef FUNCTION
void investigate (int argc, char* argv[])
#else
int main (int argc, char* argv[])
#endif
{
    

    if (argc <=1) {
        DIR *dp;
        struct dirent *dirp;
            //fprintf(stderr, "Usage: ./program directory_name\n");
            //exit(EXIT_FAILURE);
        char * path [100];
        getcwd(path,100);
    
        argv[1] = path;
        if ((dp = opendir(argv[1])) == NULL) {
             perror("ERROR");
        }

        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_REG){ //ONLY FILES ARE PRINTeD, NO DIRECTORIES.
                //printf("%hhu\n", dirp -> d_type);
                
                if(!strstr(dirp->d_name,".")){ //dicarding hidden files "."
                    printf("\n%s\n\n", dirp->d_name);
                }
            }

        if (closedir(dp) == -1)
            perror("closedir");

    }else if(argc==2){


        int fd = open(argv[1], O_RDONLY); 

        if(fd<0){

            puts("There is no such object to investigate...");
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

}