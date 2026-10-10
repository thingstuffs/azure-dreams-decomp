#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/object_flags.h"




/* Updates a countdown-driven visual and clears its owner slot when the countdown expires. */
void func_8002407C(void *state, void *unused, void *visual) {
    s32 remaining_ratio;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)state + 0x2C) - 1;
    remaining_ratio = (s32)((s32)(ticks_left << 16) >> 9) /
               (s16)*(u16 *)((u8 *)state + 0x2E);
    D_800269B4 = 1;
    *(u16 *)((u8 *)state + 0x2C) = ticks_left;
    *(u8 *)((u8 *)visual + 0x0E) += 4;
    *(s8 *)((u8 *)visual + 0x0D) = (s8)remaining_ratio;
    *(s8 *)((u8 *)visual + 0x0C) = (s8)remaining_ratio;
    if (*(s16 *)((u8 *)visual + 6) >= -6) {
        *(s16 *)((u8 *)visual + 6) -= 2;
    }
    if (*(s16 *)((u8 *)state + 0x2C) <= 0) {
        s16 *owner_slot;
        s32 slot_offset;
        s32 owner_addr;

        slot_offset = *(s16 *)((u8 *)state + 0x50) * 2;
        owner_addr = *(s32 *)((u8 *)state + 0x7C);
        owner_slot = (s16 *)(slot_offset + owner_addr + 0x64);
        *owner_slot = 0;
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
