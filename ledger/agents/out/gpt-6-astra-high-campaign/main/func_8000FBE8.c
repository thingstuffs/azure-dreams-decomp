#include "common.h"

/* Record the maximum string length and last nonempty slot across five strings. */
void func_80022BE8(u8 *text_block)
{
    u8 **strings;
    u8 *text;
    u8 *next_text;
    s32 longest;
    s32 last_nonempty;
    s32 length;
    s32 string_index;
    u8 character;

    longest = 0;
    last_nonempty = longest;
    string_index = longest;
    strings = (u8 **)text_block;
    do {
        length = 0;
        text = *strings;
        goto check;
        do {
            length++;
            text = next_text;
            last_nonempty = string_index;
            if (longest < length) {
                longest = length;
            }
check:
            character = *text;
            next_text = text + 1;
        } while (character != 0);
        string_index++;
        strings++;
    } while (string_index < 5);
    text_block[0x16] = longest;
    text_block[0x17] = last_nonempty + 1;
}
