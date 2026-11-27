#include "common.h"
#include "dungeon/item.h"

extern u8 *value_sign_text_pointer[];

/* Append two bytes selected by the sign of the value, or nothing for zero. */
void *append_value_sign(s32 value, u8 *buffer) {
    u8 *dst;

    dst = buffer;
    if (value != 0) {
        u8 *src;

        src = value_sign_text_pointer[0];
        if (value <= 0) {
            src += 2;
        }

        *dst++ = *src++;
        *dst++ = *src++;
    }
    return dst;
}
