#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file.c>\n", argv[0]);
        return 1;
    }
    
    char command[256];
    snprintf(command, sizeof(command), "gcc %s -o output && ./output", argv[1]);
    
    int ret = system(command);
    if (ret != 0) {
        printf("Compilation or execution failed.\n");
        return 1;
    }
    
    return 0;
}
