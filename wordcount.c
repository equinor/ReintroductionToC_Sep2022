#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    bool print_nw = false;
    bool print_nc = false;
    const char * filename = NULL;

    while (--argc > 0 && (*++argv)[0] == '-') {
        int c;
        while (c = *++argv[0]) {
            switch (c) {
                case 'w':
                    print_nw = true;
                    break;
                case 'c':
                    print_nc = true;
                    break;
                default:
                    printf("wordcount: illegal option %c\n", c);
                    argc = 0;
                    return EXIT_FAILURE;
            }
        }
    }

    if (argc) {
        filename = argv[0];
        --argc;
    }

    if (argc != 0) {
        printf("usage: wordcount [-w] [FILE]\n");
        return EXIT_FAILURE;
    }

    FILE * fp = stdin;
    if (filename) {
        fp = fopen(filename, "r");
        if (!fp) {
            perror("Unable to open file\n");
            return EXIT_FAILURE;
        }
    }

    int ch = 0;
    int nl = 0;
    int nw = 0;
    int nc = 0;
    bool inside_a_word = false;

    while ((ch = getc(fp)) != EOF) {
        ++nc;
        if (ch == '\n')
            ++nl;
        if (ch == ' ' || ch == '\n' || ch == '\t')
            inside_a_word = false;
        else if (!inside_a_word) {
            inside_a_word = true;
            ++nw;
        }
    }

    if (print_nw)
        printf("%d\n", nw);

    if (print_nc)
        printf("%d\n", nc);

    if (!print_nc && !print_nw)
        printf("%d %d %d\n", nl, nw, nc);

    if (filename)
        fclose(fp);

    return 0;
}
