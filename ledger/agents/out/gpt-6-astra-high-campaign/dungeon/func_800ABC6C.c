#include "common.h"

/* Applies a flag mask to each record through the terminal record. */
void func_800B13CC(void *record, s32 flag_mask) {
    u16 *flags;

    for (;;) {
        flags = (u16 *)((u8 *)record + 4);
        *flags = (u16)(*flags | flag_mask);
        if (*(s8 *)record < 0) {
            return;
        }
        record = (u8 *)record + 12;
    }
}
