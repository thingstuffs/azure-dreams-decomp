#include "common.h"

extern void func_800478B8(void *arg0);

extern struct {
    s32 value;
    s32 pad[2];
} D_800814A0;

/* Propagate the high flag bit and process each entry in the block. */
void func_800D78C0(void *block) {
    s32 entry_index;

    if (*(*(u16 **)((u8 *)block + 0x98)) & 0x8000) {
        *((u16 *)block - 1) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

    for (entry_index = 0; entry_index < *(s16 *)((u8 *)block + 2); entry_index++) {
        func_800478B8((u8 *)block + 8 + entry_index * 0x30);
    }
}
