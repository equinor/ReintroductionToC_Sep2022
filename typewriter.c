#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

int verboselevel = 0;

int main(int argc, char ** argv)
{
    int opt;
    int msec = 100;
    bool upcase = false;

    while ((opt = getopt(argc, argv, "uvt:")) != -1) {
        switch (opt) {
        case 'u':
            upcase = true;
            break;
        case 't':
            msec = atoi(optarg);
            break;
        case 'v':
            ++verboselevel;
            break;
        default:
            fprintf(stderr, "Usage: %s [-t msec] [-u] words...\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (verboselevel > 0) {
        size_t nwords = argc - optind;
        printf("upcase = %s, msec = %d, nwords = %zu\n", upcase ? "true" : "false", msec, nwords);
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected some words to work with\n");
        exit(EXIT_FAILURE);
    }

    for (int i = optind; i < argc; ++i) {
        const char * s = argv[i];
        while (*s) {
            long delay_ms = rand() % (msec * 2);
            thrd_sleep(&(struct timespec){.tv_nsec=(delay_ms*1000*1000)}, NULL);
            int ch = *s++;
            if (upcase)
                ch = toupper(ch);
            putchar(ch);
            fflush(stdout);
        }
        putchar(' ');
        fflush(stdout);
    }
    putchar('\n');

    return EXIT_SUCCESS;
}
