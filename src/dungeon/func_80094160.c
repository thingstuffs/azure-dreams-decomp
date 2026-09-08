#include "common.h"

extern u8 D_800E045F[];

/* Copies two bytes from D_800E045F to the output for a full-width Latin vowel. */
void *func_800998C0(void *dst, void *character) {
    u8 second_byte;
    u8 *out = dst;
    u8 *src = D_800E045F;

    if ((*(u8 *)character == 0x82) &&
        ((second_byte = *((u8 *)character + 1), (second_byte == 0x81)) ||
         (second_byte == 0x89) || (second_byte == 0x95) ||
         (second_byte == 0x85) || (second_byte == 0x8F) ||
         (second_byte == 0x60) || (second_byte == 0x68) ||
         (second_byte == 0x74) || (second_byte == 0x64) ||
         (second_byte == 0x6E))) {
        *out++ = src[0];
        *out++ = src[1];
    }
    return out;
}
