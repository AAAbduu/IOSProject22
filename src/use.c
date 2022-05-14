#include <fcntl.h>
#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <libgen.h>


extern int errno;

int main(int argc,const char *argv[]){

    char path[PATH_MAX];
    getcwd(path, sizeof(path));

    char currpath[PATH_MAX];
    getcwd(currpath, sizeof(currpath));

    char *last = strrchr(currpath, '/');

    char *whereAmI = last+1;

    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/gameTree/inventory");

    char objectTry [456];

    strcpy(objectTry, path);

    strcat(objectTry, "/");


       
        if(argc==3){
            int object,toUse;
            
            if(strcmp(whereAmI, "Castle")==0 && strcmp(argv[1], "royalSeal")==0 && strcmp(argv[2], "royalGuard")==0){
                strcat(objectTry, "item-");
                strcat(objectTry, argv[1]);
                strcat(objectTry, ".txt");
                object = open(objectTry,O_RDONLY );
                if(object<0){
                    printf("I don't have that object");
                    return -1;
                }
                char openPath [456];
                getcwd(openPath, sizeof(openPath));
                strcat(openPath,"/MainHall");
                unsigned long mode = strtoul("40755", NULL, 8);
                chmod(openPath,mode);
                unlink(objectTry);
                printf("RoyalGuard: Oh, you are the most legendary king guard, we are sorry. Go in, talk with you Grace.\n\n");
                return 0;
            }
            else if(strcmp(whereAmI, "Castle")==0 && strcmp(argv[1], "parkKey")==0 && strcmp(argv[2], "Park")==0){
                strcat(objectTry, "item-");
                strcat(objectTry, argv[1]);
                strcat(objectTry, ".txt");
                object = open(objectTry,O_RDONLY );
                if(object<0){
                    printf("I don't have that object");
                    return -1;
                }
                char openPath [456];
                getcwd(openPath, sizeof(openPath));
                strcat(openPath,"/Park");
                unsigned long mode = strtoul("40755", NULL, 8);
                chmod(openPath,mode);
                unlink(objectTry);
                printf("Park opened...");
                return 0;
            }
            else if(strcmp(whereAmI, "MainSquare")==0 && strcmp(argv[1], "possibleKid")==0 && strcmp(argv[2], "mother")==0){
                strcat(objectTry, "char-");
                strcat(objectTry, argv[1]);
                strcat(objectTry, ".txt");
                object = open(objectTry,O_RDONLY );
                if(object<0){
                    printf("I don't know who is that kid");
                    return -1;
                }
                printf("Mother: That is not my child, you idiot!.\n My child does not do any drugs.\nNOT LIKE YOU!\n\n");
                unlink(objectTry);
                return 0;
            }
            else if(strcmp(whereAmI, "MainSquare")==0 && strcmp(argv[1], "kid")==0 && strcmp(argv[2], "mother")==0){
                strcat(objectTry, "char-");
                strcat(objectTry, argv[1]);
                strcat(objectTry, ".txt");
                object = open(objectTry,O_RDONLY );
                if(object<0){
                    printf("I don't know who is that kid");
                    return -1;
                }
                printf("GREAT WORK, YOU SOLVED THE CASE, YOU MAY EXPLORE THE WORLD BUT THERE IS NOT MUCH TO DO LEFT.\n\n");
                unlink(objectTry);
                return 0;
            }
        }
        return 1;
    }

