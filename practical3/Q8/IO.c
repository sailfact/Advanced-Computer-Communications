#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> //needed for open
#include <sys/stat.h>  //needed for open
#include <fcntl.h>     //needed for open

#define MAX 20

int main(int argc, char **argv) {
    int inFile;
    int n_char=0;
    char buffer[10];

    inFile=open(argv[1],O_RDONLY);
    if (inFile==-1)
    {
            exit(1);
    }

    //Use the read system call to obtain 10 characters from inFile
    while( (n_char=read(inFile, buffer, MAX))!=0)
    {
            //Display the characters read
            n_char=write(1,buffer,n_char);
            sleep(1);
    }

    return 0;
}