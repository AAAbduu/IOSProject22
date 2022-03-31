#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



    int main(int argc, char *argv[])
    {
      DIR* dir_ptr;     // the directory
      struct dirent* direntp;


        char src_folder[256];


        dir_ptr = opendir("."); //open directory
        if ( dir_ptr == NULL )
        {
            perror( "." );
            exit( 1 );

        }
        rename(src_folder, "."src_folder);
        closedir( dir_ptr );

        return 0;
    }
