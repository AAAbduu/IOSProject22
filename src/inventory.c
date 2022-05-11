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
    if(argc ==1){
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
           if(strstr(dirp->d_name,"item-") || strstr(dirp->d_name,"char-")){ //printing only items.
                    char item[30];
                    strcpy(item,dirp->d_name);
                    char *last = strchr(item,'-');
                    char itemname[15];
                    memset(itemname, 0, sizeof itemname); //resetting the array
                    int i = 1;
                    while(last[i]!='.'){
                        if(last[i]!='.'){
                            itemname[i-1] = last[i];
                            i++;
                        }
                    }
                    printf("\n%s\n\n", itemname);
                    memset(itemname, 0, sizeof itemname); //resetting the array
               }

    closedir(dp);
    }else if(argc==2){
        if(strstr(argv[1], "possiblekid") !=NULL|| strstr(argv[1], "kid")!=NULL){
            printf("I should not torture the kid...\n");
            return -1;
        }
         char item [30];

        memset(item, 0, sizeof item); //resetting the array


        strcpy(item, "item-");
        strcat(item,argv[1]);
        strcat(item,".txt");
        int fd = open(item, O_RDONLY);

        if(fd<0){

            puts("There is no such object in your inventory");
            return -1;

        }
        
        char buf[4096];
        int lung;

        while(lung=read(fd,buf,sizeof(buf))) //read as much as 4096 in file
        {
             puts("\n");
             write(0,buf,lung); //write on terminal
             puts("\n");
        }

        close(fd);
        memset(item, 0, sizeof item); //resetting the array
    }
}