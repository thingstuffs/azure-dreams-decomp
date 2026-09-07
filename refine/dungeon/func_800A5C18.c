#include "common.h"

typedef struct {
    u8 pad00[0xA];
    u16 fieldA;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 func_800A2B04();

/* Follows the linked position until the countdown expires, then resets and marks completion. */
s32 func_800AB378(void *state, void *transform, void *config, void *object) {
    s16 ticks_left;
    void *linked_transform;

    if (*(u16 *)((u8 *)config + 0x14) & 0x8000) {
        *(s16 *)((u8 *)state + 0x96) = 0;
    }
    if (*(s16 *)((u8 *)state + 0x96) != 0) {
        linked_transform = *(void **)((u8 *)*(void **)((u8 *)object + 0x60) - 0x18);
        *(s32 *)((u8 *)transform + 0xC) = *(s32 *)((u8 *)linked_transform + 0xC);
        *(s32 *)((u8 *)transform + 0x10) = *(s32 *)((u8 *)linked_transform + 0x10);
    }
    ticks_left = *(u16 *)((u8 *)state + 0x96) - 1;
    *(s16 *)((u8 *)state + 0x96) = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        return 0;
    }
    *(s32 *)((u8 *)transform + 0x14) = 0;
    *(s32 *)((u8 *)transform + 0x10) = 0;
    *(s32 *)((u8 *)transform + 0xC) = 0;
    func_800A2B04(transform, *((u8 *)config + 0x24), *((u8 *)config + 0x25));
    *(u16 *)((u8 *)state + 0x98) &= 0xFFF7;
    *(s32 *)((u8 *)object + 0x1C) |= 0x40000000;
    D_80083460.fieldA -= 1;
    return 1;
}
