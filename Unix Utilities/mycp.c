#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100

int main(int argc,char* argv[])
{
        char buf[COUNT];

        if(argc != 3)
        {
                printf("Usage: %s file name \n ",argv[0]);
                exit(-1);
        }

        int fd1 = open(argv[1],O_RDONLY);
        if(fd1 < 0)
        {
                printf("not open\n");
                exit(-2);
        }

        int fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC,0644);
        if(fd2 < 0)
        {
                printf("not open\n");
                exit(-3);
        }


        int num_read;
        while(( num_read = read(fd1,buf,COUNT)) > 0)
        {
                if(write(fd2,buf,num_read) < 0)
                {
                        printf("not write");
                        exit(-4);
                }
        }

        close(fd1);
        close(fd2);

        return 0;
}
