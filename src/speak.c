#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>


int main (int argc, char* argv[])
{
    if (argc <=1) {
        DIR *dp;
        struct dirent *dirp;
        char path [100];
        getcwd(path,100);
    
        argv[1] = path;
        if ((dp = opendir(argv[1])) == NULL) {
             perror("ERROR");
        }

        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_REG){ //ONLY FILES ARE PRINTeD, NO DIRECTORIES.
                //printf("%hhu\n", dirp -> d_type);
                
                if(strstr(dirp->d_name,"char-")){ //printing only characters.
                    char character[30];
                    strcpy(character,dirp->d_name);
                    char *last = strchr(character,'-');
                    printf("\n%s\n\n", last+1);
                    
                }
            }

        if (closedir(dp) == -1)
            perror("closedir");

    }else if(argc==2){

        char character [30];

        strcpy(character, "char-");
        strcat(character,argv[1]);
        int fd = open(character, O_RDONLY); 

        if(fd<0){

            puts("Who? Are you talking with ghosts?");
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