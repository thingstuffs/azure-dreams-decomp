#include "common.h"

/* Formats `value` as a right-justified decimal number into buf[0..width-1]:
 * writes digits from the least significant end (buf[width-1]) leftward;
 * once the running quotient (value/10) reaches zero, remaining (more
 * significant) positions are space-padded instead of getting '0' digits. */
void func_800537D0(s32 value, s32 width, char *buf)
{
    s32 flag;
    s32 i;
    char *p;

    flag = 0;
    i = width - 1;
    if (i < 0)
        return;
    do {
        p = buf + i;
        if (flag == 0)
            *p = (char)((value % 10) + '0');
        else
            *p = ' ';
        if ((value = value / 10) == 0)
            flag = 1;
        i--;
    } while (i >= 0);
}
