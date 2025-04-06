#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int femtoshell_main(int argc, char *argv[]) {
    char input[1000000];
    
    while(1){
        
        printf(" Femto shell -> ");
        
        if(fgets(input, 1000000, stdin) == NULL)
            break;
        
        input[strcspn(input, "\n")] = '\0';

        if(*input == NULL)
            continue;
        if(strncmp(input, "echo ", 5) == 0)
            printf("%s\n", input + 5);
        else if (strcmp(input, "exit") == 0)
        { 
            printf("Good Bye\n");
            break;
        }
        else
            printf("Invalid command\n");
    }
    return 0;
}
