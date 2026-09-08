#include "common.h"

/* Returns whether the string contains a character other than a space or newline. */
s32 func_8004E8D8(u8 *text)
{
    s32 has_content = 0;
    s32 character;
    s32 space;
    s32 newline;
    u8 text_byte = *text;

    if (text_byte == 0) {
        goto done;
    }
    space = 0x20;
    newline = 0x0A;

loop:
    character = text_byte & 0xFF;
    if (character == space) {
        goto next;
    }
    if (character == newline) {
        goto next;
    }
    has_content = 1;
    goto done;

next:
    text++;
    text_byte = *text;
    if (text_byte != 0) {
        goto loop;
    }

done:
    return has_content;
}
