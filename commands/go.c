#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>


void go (int argc, char* argv[]){

    if(argv[1] == NULL){
        printf("Where should i go?\n Print possible goto places");
    }else if(strcmp(argv[1],"back")==0){
        chdir("..");
        char cwd[200];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
        
    }else if(chdir(argv[1])<0){
    printf("I cant go there!\n ");
    }else{
        char cwd[200];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
     }
    }

    //RETURN TO PARENT DIRECTORY OR MAY BE CHANGE ENVIRONMENT VARIABLE.
    
}  

 int main(int argc, char* argv[]){

    go (argc, argv);  //IN ORDER TO WORK INDPENDENTLY, UNCOMMENT THIS FUNCTION, COMPILE, EXECUTE...
    
} 


