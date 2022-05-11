#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>

int main (int argc, char* argv[])
{
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/gameTree/inventory");
    int fd = open(path, O_RDONLY);
    if (fd < 0){
        printf("Can't open inventory\n");
    }else{
        char c;
        printf("Inventory:\n");
        while (read(fd, &c, 1) > 0)
        {
            printf("%c",c);
        }

        close(fd);
    }

}