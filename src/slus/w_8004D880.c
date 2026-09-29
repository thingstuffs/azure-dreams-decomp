#include "common.h"

extern s32 func_8004D828(s32);

/* Converts fullwidth alphanumerics to ASCII, delegating other character codes. */
s32 func_8004D880(s32 char_code)
{
    s32 code;
    s32 letter_code;
    s32 range_index;
    s32 output_char;

    if (char_code & 1) {
        code = char_code;
    } else {
        code = char_code;
    }

    if (code & 2) {
        range_index = code + 0x7DB1;
    } else {
        range_index = code + 0x7DB1;
    }
    char_code = code;
    if ((u32)(range_index & 0xFFFF) < 10) {
        output_char = range_index + 0x30;
        return output_char & 0xFF;
    }

    if (code & 4) {
        letter_code = code;
    } else {
        letter_code = code;
    }
    if (letter_code & 8) {
        range_index = letter_code + 0x7DA0;
    } else {
        range_index = letter_code + 0x7DA0;
    }
    if ((u32)(range_index & 0xFFFF) < 26) {
        output_char = range_index + 0x41;
        return output_char & 0xFF;
    }

    letter_code += 0x7D7F;
    if ((u32)(letter_code & 0xFFFF) < 26) {
        output_char = letter_code + 0x61;
    } else {
        output_char = func_8004D828(char_code & 0xFFFF);
    }

    return output_char & 0xFF;
}
