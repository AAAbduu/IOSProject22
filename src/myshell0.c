// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20

char BINPATH [456];

char PREV_PATH [456];

char HISTPATH [456];

char MANPATH [456];

/////////// reading commands:



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

    if(argv[1] == NULL){
        printf("Where should i go?\n\n");
        DIR *dp;
        struct dirent *dirp;
        char * path [100];
        getcwd(path,100);
        argv[1] = path;
        char cwd[200];
        getcwd(cwd, sizeof(cwd));
        char *last = strrchr(cwd, '/');
        if(strcmp(last+1,"Home")<0){
            puts("Back");
        }
        if ((dp = opendir(argv[1])) == NULL) {
             perror("ERROR");
        }
        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_DIR){ //ONLY directories ARE PRINTeD, NO files.
               // printf("%hhu\n", dirp -> d_type);
                if(!strstr(dirp->d_name,".")){ //dicarding hidden directories "."
                    printf("%s\n\n", dirp->d_name);
                }
            }

        if (closedir(dp) == -1)
            perror("closedir");


    }else if(strcmp(argv[1],"back")==0){
        char cwd[200];
        getcwd(cwd, sizeof(cwd));
        char *last = strrchr(cwd, '/');
        if(strcmp(last+1,"Home")<0){
        chdir("..");
        }else{
            puts("I can't go back anymore!");
        }
        
        
    }else if(chdir(argv[1])<0){
    printf("I can't go there!\n ");
    }  
}  



///////////////////////////////////////

int executeChild(char *commandPath[],char *argv[]){
   pid_t pid, wpid;
   int status;
   pid = fork();
        
      if(pid ==0){
         execvp(commandPath,argv);
         exit(0);
      }
      while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes
   

}


int execute(int argc, char *argv[])
{
    pid_t pid, wpid;
    int status;
    char commandPath[456];
		// If the quit statement is found 
		if(strcmp(*(argv), "quit") == 0)			
			exit(0);
		
		if(strcmp(argv[0], "go") == 0) {
			go(argc, argv);

		}		
      if(strcmp(argv[0], "myman") == 0) {
         getcwd(PREV_PATH,sizeof(PREV_PATH));
         chdir(MANPATH);
         strcpy(commandPath,BINPATH);
         strcat(commandPath,"/myman");

         int x = executeChild(commandPath, argv); 

         chdir(PREV_PATH);
         return x;
      }

      if(strcmp(argv[0], "history") == 0) {
         getcwd(PREV_PATH,sizeof(PREV_PATH));
         chdir(HISTPATH);
         strcpy(commandPath,BINPATH);
         strcat(commandPath,"/history");
         int x = executeChild(commandPath, argv);
         chdir(PREV_PATH);
         return x;
      }
//GENERAL CASE IF NO SPECIAL CASE IS DETECTED
      strcpy(commandPath,BINPATH);
      strcat(commandPath,"/");
      strcat(commandPath,argv[0]);
      int x = executeChild(commandPath,argv);
		return x;

}




int main ()
{
   getcwd(BINPATH,sizeof(BINPATH)); //GETTING CONSTANT BINPATH GLOBAL VARIABLE PATH
   getcwd(HISTPATH,sizeof(HISTPATH)); //GETTING CONSTANT HISTPATH GLOBAL VARIABLE PATH
   getcwd(MANPATH,sizeof(MANPATH)); //GETTING CONSTANT MANPATH GLOBAL VARIABLE PATH

   strcat(HISTPATH, "/gameTree");
   strcat(BINPATH,"/bin");
   strcat(MANPATH,"/manpages");
   chdir("gameTree/Home");
   char dir [MAXLINE]; 
   getcwd(dir, sizeof(dir));
   char *last = strrchr(dir, '/');
   char * Prompt = strcat(last+1, ">");
   int eof= 0;
   int argc;
   char *args[MAXARGS];

    
   while (1) {
      getcwd(dir, sizeof(dir));
      char *last = strrchr(dir, '/');
      char * Prompt = strcat(last+1, ">");
      write(0,Prompt, strlen(Prompt));
      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         if(strcmp(args[0], "history")!=0 && argc >1){
            pid_t pid, wpid;
            int status;
            getcwd(PREV_PATH,sizeof(PREV_PATH));
            chdir(HISTPATH);
            char commandPath[456];
            strcpy(commandPath,BINPATH);
            strcat(commandPath,"/history");
            pid = fork();
        
            if(pid ==0){
            execvp(commandPath,args);
            exit(0);
         }
            while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes 
            chdir(PREV_PATH);
         }
         execute(argc, args);
      }
 
      if (eof) exit(0);
   }
}