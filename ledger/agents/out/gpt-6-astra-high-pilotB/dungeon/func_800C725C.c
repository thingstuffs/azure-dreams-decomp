#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_800814A0[3];

/* Decrement the entry count and flag the entry and global state when it reaches zero. */
void func_800CC9BC(void *entry) {
    u8 remaining_count;

    remaining_count = *(u8 *)((u8 *)entry + 7) - 1;
    *(u8 *)((u8 *)entry + 7) = remaining_count;
    if (!(remaining_count & 0xFF)) {
        D_80083460.fieldA = (u16)(D_80083460.fieldA - 1);
        *(u16 *)((u8 *)entry - 2) =
            (u16)(*(u16 *)((u8 *)entry - 2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
