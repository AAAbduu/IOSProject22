#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>


int main (int argc, char* argv[])
{
    if (argc <=1) {
        DIR *dp;
        struct dirent *dirp;
        char path [PATH_MAX];
        getcwd(path,PATH_MAX);
    
        argv[1] = path;
        if ((dp = opendir(argv[1])) == NULL) {
             perror("ERROR");
             return -1;
        }

        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_REG){ //ONLY FILES ARE PRINTeD, NO DIRECTORIES.
                //printf("%hhu\n", dirp -> d_type);
                if(strstr(dirp->d_name,"item-")){ //printing only items.
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
                
            }

        if (closedir(dp) == -1){
            perror("closedir");
            return -1;
        }

        return 0;

    }else if(argc==2){


       char item [30];

        strcpy(item, "item-");
        strcat(item,argv[1]);
        strcat(item,".txt");
        int fd = open(item, O_RDONLY);

        if(fd<0){

            puts("There is no such object to investigate...");
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

        if(strcmp(argv[1],"brokenbeerglass") == 0){
            unsigned long mode = strtoul("40755", NULL, 8);
            chmod("../../Pub",mode);
            printf("May be i should leave it for today and go get a drink....\n\n");
            
        }

        close(fd);
        return 0;
    }

}