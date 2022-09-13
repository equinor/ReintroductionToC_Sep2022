#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int ch;
    while ((ch = getc(stdin)) != EOF)
        putc(tolower(ch), stdout);
    return 0;
}
