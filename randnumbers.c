#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("usage: randnumbers NUM\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    int count = atoi(argv[1]);
    while (count--) {
        int num = rand();
        printf("%d\n", num);
    }

    return EXIT_SUCCESS;
}
