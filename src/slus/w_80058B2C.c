#include "common.h"

extern int func_800589B8(int a0);
extern int func_80058AA8(int a0, int a1);

/* Combines the low bytes of two successive calls with the same input and returns the low 16 bits. */
int func_80058B2C(int input)
{
    int first_result;
    int second_result;

    first_result = func_800589B8(input);
    second_result = func_800589B8(input);
    return func_80058AA8(first_result & 0xFF, second_result & 0xFF) & 0xFFFF;
}
