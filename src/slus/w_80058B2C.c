#include "common.h"

extern int slusReadNextByteAndFinish(int a0);
extern int packBigEndianHalfword(int a0, int a1);

/* Combines the low bytes of two successive calls with the same input and returns the low 16 bits. */
int func_80058B2C(int input)
{
    int first_result;
    int second_result;

    first_result = slusReadNextByteAndFinish(input);
    second_result = slusReadNextByteAndFinish(input);
    return packBigEndianHalfword(first_result & 0xFF, second_result & 0xFF) & 0xFFFF;
}
