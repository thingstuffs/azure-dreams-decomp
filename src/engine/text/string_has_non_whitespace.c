#include "common.h"
#include "engine/text.h"

/* Returns whether the string contains a character other than a space or newline. */
s32 string_has_non_whitespace(u8 *text)
{
    s32 has_content = 0;
    s32 character;
    s32 space;
    s32 newline;
    u8 text_byte = *text;

    if (text_byte != 0) {
        space = 0x20;
        newline = 0x0A;

        while (text_byte != 0) {
            character = text_byte & 0xFF;
            if (character != space) {
                if (character != newline) {
                    has_content = 1;
                    break;
                }
            }
            text++;
            text_byte = *text;
        }
    }
    return has_content;
}
