#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc <=1) {
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
                printf("%s\n", dirp->d_name);
            }

        if (closedir(dp) == -1)
            perror("closedir");

    }else if(argc==2){
        int fd = open(argv[1], O_RDONLY); 
        //int bytes = read (fd,content,sizeof(content)-1);
        //write(1,content,bytes);
        printf("fd = %d/n", fd); 
        if ((dp = opendir(argv[1])) == NULL) {
        perror("ERROR");
    }
        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_REG){ //ONLY FILES ARE PRINTeD, NO DIRECTORIES.
                //printf("%hhu\n", dirp -> d_type);
                printf("%s\n", dirp->d_name);
            }

    if (closedir(dp) == -1)
        perror("closedir");

    }

    exit(EXIT_SUCCESS);
}