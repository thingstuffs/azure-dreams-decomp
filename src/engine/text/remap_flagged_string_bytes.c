#include "common.h"

extern u8 glyph_code_flags[0x100];

/* Adds 0x31 to characters flagged 0x10 in a nul-terminated string and returns its original pointer. */
u8 *remap_flagged_string_bytes(u8 *string) {
    u8 *cursor = string;
    u8 *char_flags;
    u8 character;

    if (*string == 0) {
        return string;
    }
    char_flags = glyph_code_flags;
    do {
        character = *cursor;
        if (char_flags[character] & 0x10) {
            *cursor = character + 0x31;
        }
        cursor++;
    } while (*cursor != 0);
    return string;
}
