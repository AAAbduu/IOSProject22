#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <libgen.h>


int copyfile1(char* infilename, char* outfileDir) {
    FILE* infile; //File handles for source and destination.
    FILE* outfile;
    char outfilename[PATH_MAX];

    infile = fopen(infilename, "r"); // Open the input and output files.
    if (infile == NULL) {
      return 1;
    }
    sprintf(outfilename, "%s/%s", outfileDir, basename(infilename));

    outfile = fopen(outfilename, "w");

    char buf[4096];
             int lung;

            while(fgets(buf,sizeof(buf), infile)) //read as much as 4096 in file
            {
                fputs(buf,outfile); //COPY CONTENT OF FILE 
            }
            fclose(infile);
            fclose(outfile);
}

int main (int argc, char* argv[])
{
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/gameTree/inventory");
        char object [30];

        strcat(object, "item-");
        strcat(object, argv[1]);
        strcat(object, ".txt");
        int obj = open(object, O_RDONLY);
        if(obj < 0){
            printf("There isn't such object\n");
        }else{
            char objectPath[PATH_MAX];
            getcwd(objectPath, sizeof(objectPath));
            strcat(objectPath, "/");
            strcat(objectPath, object);
            copyfile1(objectPath, path);    
           }
}



