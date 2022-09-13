#include "tempconv.h"

#include <stdio.h>

static void print_temp_table(int lower, int upper, int step)
{
    for (int celsius = lower; celsius <= upper; celsius += step) {
        int fahr = to_fahrenheit(celsius);
        printf("%4d %4d\n", celsius, fahr);
    }
}

int main(void)
{
    int lower_limit = -90;
    int upper_limit = 60;
    int temp_step = 10;

    print_temp_table(lower_limit, upper_limit, temp_step);

    return 0;
}
