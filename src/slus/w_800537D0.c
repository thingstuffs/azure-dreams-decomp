#include "common.h"

/* Writes a right-justified decimal value into a fixed-width buffer with leading spaces. */
void func_800537D0(s32 value, s32 width, char *buf)
{
    s32 pad_spaces;
    s32 column;
    char *digit_pos;

    pad_spaces = 0;
    column = width - 1;
    if (column < 0)
        return;
    do {
        digit_pos = buf + column;
        if (pad_spaces == 0)
            *digit_pos = (char)((value % 10) + '0');
        else
            *digit_pos = ' ';
        if ((value = value / 10) == 0)
            pad_spaces = 1;
        column--;
    } while (column >= 0);
}
