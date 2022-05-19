// myShell0
//////////////////////////////////////////////////

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

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20
char BINPATH [456];


/////////// reading commands:


void initialize(){
   getcwd(BINPATH,sizeof(BINPATH)); //GETTING CONSTANT BINPATH GLOBAL VARIABLE PATH
   strcat(BINPATH,"/bin");
   chdir("gameTree/Home");
   //unsigned long mode = strtoul("40755", NULL, 8);
   chmod("MainSquare/Pub", 0);
   chmod("MainSquare/Castle/MainHall", 0);
   chmod("MainSquare/Castle/Park", 0);

}

void red () {
  printf("\033[1;31m");
}
void green() {
  printf("\033[0;32m");
}
void reset () {
  printf("\033[0m");
}


int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
   int ret,i;

   *argcp = 0;
   *eofp = 0;
   i=0;
   while ((ret=read(0,cmd+i,1)) == 1) {
      if (cmd[i]=='\n') break;  // correct line
      i++;
      if (i>=MAXLINE) {
         ret=-2;        // line too long
         break;
      }
   }
   switch (ret)
   {
     case 1 : cmd[i+1]='\0';    // correct reading 
              break;
     case 0 : *eofp = 1;        // end of file
              return 0;
              break;
     case -1 : *argcp = -1;     // reading failure
              fprintf(stderr,"Reading failure \n");
              return 0;
              break;
     case -2 : *argcp = -1;     // line too long
              fprintf(stderr,"Line too long -- removed command\n");
              return 0;
              break;
   }
   // Analyzing the line
   cmdp= cmd;
   for (i=0; i<max; i++) {  /* to show every argument */
      if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
      cmdp= NULL;
   }
   if (i >= max) {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   *argcp= i;
   return 1;
}


int go (int argc, char* argv[])
{
   char * path [456];
   getcwd(path,sizeof path);

    if(argv[1] == NULL){
        printf("Where should i go?\n\n");
        DIR *dp;
        struct stat file;
        struct dirent *dirp;
        
        argv[1] = path;
        char cwd[456];
        getcwd(cwd, sizeof(cwd));
        char *last = strrchr(cwd, '/');
        if(strcmp(last+1,"Home")!=0){
            puts("Back\n");
        }
        if ((dp = opendir(argv[1])) == NULL) {
             perror("ERROR");
        }
        unsigned long mode = strtoul("40755", NULL, 8);
        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_DIR){ //ONLY directories ARE PRINTeD, NO files.
               // printf("%hhu\n", dirp -> d_type);
                if(!strstr(dirp->d_name,".")){ 
                    stat(dirp->d_name, &file);
                    if(file.st_mode == mode){
                       green();
                     printf("%s    Open\n\n", dirp->d_name);
                    }else{
                       red();
                       printf("%s    Closed\n\n", dirp->d_name);
                    }
                    reset();
                }
            }

        if (closedir(dp) == -1){
            perror("closedir");
            return -1;
        }
      return 0;
    }else if(strcmp(argv[1],"back")==0){
        char cwd[456];
        getcwd(cwd, sizeof(cwd));
        char *last = strrchr(cwd, '/');
        if(strcmp(last+1,"Home")!=0){
         chdir("..");
         char preNotes [456];
         strcpy(preNotes, path);
         strcat(preNotes, "/item-notes.txt");

         char cwd [456];
         getcwd(cwd, sizeof cwd);

         strcat(cwd, "/item-notes.txt");
         int linked = link(preNotes,cwd);

         //printf("linked? : %d\n", linked);

         int unlinked = unlink(preNotes);

         //printf("unlinked? : %d\n", unlinked);
         return 0;
        }else{
            puts("I can't go back anymore!");
            return -1;
        }
        
        
    }else if(chdir(argv[1])>=0){
      char preNotes [456];
      strcpy(preNotes, path);
      strcat(preNotes, "/item-notes.txt");

      char cwd [456];
      getcwd(cwd, sizeof cwd);

      strcat(cwd, "/item-notes.txt");
      int linked = link(preNotes,cwd);

      //printf("linked? : %d\n", linked);

      int unlinked = unlink(preNotes);

      //printf("unlinked? : %d\n", unlinked);

    return 0;
    }else{
      printf("I can't go there!\n ");
      return -1;
    }
}  



///////////////////////////////////////

int executeChild(char *commandPath[],char *argv[]){
   pid_t pid, wpid;
   int status,x;

   pid = fork();
        
      if(pid ==0){
          x = execvp(commandPath,argv);
      }else{
         while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes
      }
      return x;
   

}


int execute(int argc, char *argv[])
{
    char commandPath[456];

    //printf("%s : nARgs : %d\n", argv[0], argc);

		// If the quit statement is found 
		if(strcmp(*(argv), "quit") == 0)			
			exit(0);
		
		if(strcmp(argv[0], "go") == 0) {
			int x = go(argc, argv);
        // printf("%d GO\n", x);
         return x;

		}		
//GENERAL CASE IF NO SPECIAL CASE IS DETECTED
      strcpy(commandPath,BINPATH);
      strcat(commandPath,"/");
      strcat(commandPath,argv[0]);
      //printf("\nPath : %s\n", commandPath);
      //printf("Arg 0 : %s and Arg 1 : %s", argv[0], argv[1]);
      int x = executeChild(commandPath,argv);
      //printf("\nANYOTHER COMMAND: %d", x);
		return x;

}


int main ()
{
   initialize();


   char dir [MAXLINE]; 
   getcwd(dir, sizeof(dir));
   char *last = strrchr(dir, '/');
   char * Prompt = strcat(last+1, ">");
   int eof= 0;
   int argc;
   
   char *args[MAXARGS];
  

    while (1) {
   int i = 0, x = 0;
   int lastCommand = 0;
   int nArgs = 0;
   int pipeFlag  =0;
   int execution = 0;

    getcwd(dir, sizeof(dir));
      char *last = strrchr(dir, '/');
      char * Prompt = strcat(last+1, ">");
      write(0,Prompt, strlen(Prompt));
      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         int t;
         for(t = 0; t< argc; t++){
            if(strcmp(args[t], "|")==0){
               pipeFlag = 1;
            }
         }
      if(pipeFlag==1){
         char *myArgs[20];
         int     fd[2], nbytes;
         pid_t   childpid, wpid;
         char    readbuffer[456];
         int status;

            while(execution ==0 && i<argc){
               
               if(strcmp(args[i], "|")!=0){
                  myArgs[x] = args[i];
                  nArgs++;
                  if(i+1<argc){
                     i++;
                     x++;
                  }else{
                     lastCommand = 1;
                     pipeFlag = 0;
                  }

               }
               pipe(fd);
               fflush(stdout);
               if((childpid = fork()) == -1)
               {
                  perror("fork");
                  exit(1);
               }

               if(strcmp(myArgs[0], "go")==0){
                  execution = execute(nArgs, myArgs);
                  i++;
                  x=0;
                  nArgs = 0;
               }else{

                  if(strcmp(args[i], "|")==0 || lastCommand ==1){ // execute piped commands.
                     if(childpid==0){
                        //close(fd[0]); //child closes input side of pipe
                        char * pathC [456];
                        strcpy(pathC, BINPATH);
                        strcat(pathC, "/");
                        strcat(pathC, myArgs[0]);
                        //popen(pathC, "r");
                        fflush(stdout);
                        //dup2(fd[1], STDOUT_FILENO);
                        execution = execvp(pathC, args);
                        write(fd[1],stdout,sizeof(stdout));
                        exit(0);
                     }else{
                        while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes
                        //PARENT PROCESS DOES THINGS HERE
                        close(fd[1]);
                     // dup2(fd[0], STDIN_FILENO);
                        /* Read in a string from the pipe */
                        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                      //  printf("Received string: %s", readbuffer);
                     }
                    // printf("\n%s : nARgs : %d\n", myArgs[0], nArgs);
                     //int e = execute(nArgs, myArgs);
                     //printf("\nExecution return value: %d\n", e);
                     i++;
                     x=0;
                     nArgs = 0;
                  }
                  
               }
            }
      }
         else{
            if(strcmp(args[0], "history")!=0 && argc >1){
                     char commandPath[456];
                     strcpy(commandPath,BINPATH);
                     strcat(commandPath,"/history");
                     int f = executeChild(commandPath, args);
                  }
               int e = execute(argc, args);

               //printf("Executing individual commands: %d\n", e);
         }
      }
      if (eof) exit(0);
  }
}
