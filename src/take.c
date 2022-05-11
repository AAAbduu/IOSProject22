#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<unistd.h>



int main (int argc, char* argv[])
{
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/gameTree/inventory");
    int fd = open(path, O_WRONLY | O_APPEND);

    if (fd < 0){
        printf("Can't open inventory\n");
    }else{
        int obj = open(argv[1], O_RDONLY);
        if(obj < 0){
            printf("There isn't such object\n");
        }else{
           char newname[] = ".";
           strcat(newname,argv[1]);
           if(rename(argv[1],newname) == 0){
               write(fd, argv[1], strlen(argv[1]));
               write(fd, "\n", 1);
               printf("Object added successfully\n");
               close(obj);
           }
        }
        close(fd);
    }

}