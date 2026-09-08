#include "common.h"

/* Initializes object state 0x2E with the supplied word and halfword values. */
void func_8008D368(void *object, s32 unused_1, s32 unused_2, s32 word_value, s32 halfword_value) {
    *((s8 *)object + 0x9A) = 0x2E;
    *((s8 *)object + 0x9B) = 0;
    *(s32 *)((s8 *)object + 0x8C) = 0;
    *(s32 *)((s8 *)object + 0xCC) = word_value;
    *(s16 *)((s8 *)object + 0x10E) = (s16) halfword_value;
}
