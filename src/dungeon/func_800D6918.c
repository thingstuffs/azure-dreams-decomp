#include "common.h"

/* Stores a scaled input and its complement relative to 0x57 in the record. */
void func_800DC078(void *record, s32 input_value) {
    s32 scaled_value = (s16)input_value;

    if (scaled_value < 0x80) {
        s32 half_value = scaled_value / 2;

        scaled_value = half_value + 1;
    } else {
        scaled_value = 0x40;
    }
       /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    *(s8 *)((u8 *)record + 2) = 0x57 - scaled_value;
    *(s8 *)((u8 *)record + 0xA) = scaled_value;
}
