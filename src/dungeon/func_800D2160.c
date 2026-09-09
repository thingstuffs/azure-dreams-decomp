#include "common.h"

extern void func_800478B8(void *arg0);

extern struct {
    s32 value;
    s32 pad[2];
} D_800814A0;

/* Propagate the high flag bit and process each entry in the block. */
void func_800D78C0(void *block) {
    s32 entry_index;
    s32 entry_offset;

    if (*(*(u16 **)((u8 *)block + 0x98)) & 0x8000) {
        *((u16 *)block - 1) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

    do {
        entry_index = 0;
    } while (0);
    if (*(s16 *)((u8 *)block + 2) > 0) {
        entry_offset = 8;
        do {
            func_800478B8((u8 *)block + entry_offset);
            entry_offset += 0x30;
            entry_index++;
        } while (entry_index < *(s16 *)((u8 *)block + 2));
    }
}
