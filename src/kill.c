#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

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
            if(dirp -> d_type == DT_REG){

                if(strstr(dirp->d_name,"char-")){ //get characters only
                    char character[30];
                    strcpy(character,dirp->d_name);
                    char *last = strchr(character,'-');
                    char charname[15];
                    int i = 1;
                    while(last[i]!='.'){
                        charname[i-1] = last[i];
                        i++;
                    }

                    printf("\n%s\n\n", charname);
                    memset(charname, 0, sizeof charname); //reset

                }
            }

        if (closedir(dp) == -1)
            perror("closedir");
    }

    else if(argc==2){
        char character[30];
        strcat(character, argv[1]);

        int fd = open(character, 0_RDONLY);
        if(fd<0){
            puts("Calm down! You're a man of justice, you can't kill anyone!");
            exit(0);
        }

        char buf;
        int vic,n;
        char deadchar[30];

        strcpy(deadchar, "dead-");
        strcat(deadchar, argv[1]);

        vic=open(argv[1],O_RDONLY);  // Open the File
        while((n=read(vic,&buf,1)) != 0){
            rename(charname, deadchar);
            // Initilize the killed character name by "dead-"
        }
        printf("Character killed Successfully\n");
        close(vic);
    }
return 0;
}


