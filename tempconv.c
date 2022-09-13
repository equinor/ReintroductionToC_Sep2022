#include "tempconv.h"

int to_fahrenheit(int celsius)
{
    return celsius * 9 / 5 + 32;
}

int to_celsius(int fahrenheit)
{
    return 5 * (fahrenheit - 32) / 9;
}
