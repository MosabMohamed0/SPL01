#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    char *mylocation = getcwd(NULL, 0);

    if (mylocation == NULL)
    {
        printf("pwd error");
        exit(-1);
    }
    printf("%s\n",mylocation);
    return 0;
}
