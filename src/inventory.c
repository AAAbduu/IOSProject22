#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<dirent.h>

int main (int argc, char* argv[])
{
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/gameTree/inventory");
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(path);
    printf("This is what you are carrying: \n");
    while ((dirp = readdir(dp)) != NULL)
           if(strstr(dirp->d_name,"item-")){ //printing only items.
                    char item[30];
                    strcpy(item,dirp->d_name);
                    char *last = strchr(item,'-');
                    char itemname[15];
                    int i = 1;
                    while(last[i]!='.'){
                        if(last[i]!='.'){
                            itemname[i-1] = last[i];
                            i++;
                        }
                    }
                    printf("\n%s\n\n", itemname);
               }

    closedir(dp);
}