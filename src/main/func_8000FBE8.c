#include "common.h"

void func_80022BE8(u8 *arg0)
{
    u8 **strings;
    u8 *text;
    u8 *next_text;
    s32 longest;
    s32 last_nonempty;
    s32 length;
    s32 index;
    u8 value;

    longest = 0;
    last_nonempty = longest;
    index = longest;
    strings = (u8 **)arg0;
    do {
        length = 0;
        text = *strings;
        goto check;
        do {
            length++;
            text = next_text;
            last_nonempty = index;
            if (longest < length) {
                longest = length;
            }
check:
            value = *text;
            next_text = text + 1;
        } while (value != 0);
        index++;
        strings++;
    } while (index < 5);
    arg0[0x16] = longest;
    arg0[0x17] = last_nonempty + 1;
}
