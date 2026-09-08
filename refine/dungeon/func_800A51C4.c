#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern DungeonState D_80083460;
extern s16 D_80083228[];
extern void func_80047784(void *, s32, s32);

/* Resets actor action state and selects a sprite frame for its facing direction. */
s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames)
{
    DungeonState *state = &D_80083460;

    *(u8 *)((u8 *)actor + 0x71) &= 0x7F;
    if (state->flags & 0x2008) {
        *(volatile s8 *)((u8 *)actor + 0x9A) = 0xE;
        return 1;
    }
    if (*(s32 *)((u8 *)actor + 0x1C) & 0x20) {
        register s32 dispatch_id ASM_REG("$2") = 0;
        s32 state_bits = 0xE;
        register s32 mask ASM_REG("$4");

        *(s8 *)((u8 *)actor + 0x9A) = state_bits;
        ASM_KEEP(dispatch_id);
        state_bits = *(volatile s32 *)((u8 *)actor + 0x1C);
        mask = ~0x200;
        state_bits &= mask;
        *(s32 *)((u8 *)actor + 0x1C) = state_bits;
        return;
    }

    *(s8 *)((u8 *)actor + 0x9A) = 0xD;
    *(s8 *)((u8 *)actor + 0x9B) = 0;
    *(s32 *)((u8 *)actor + 0x8C) = 0;
    if (direction_frames != 0) {
        *(u8 **)((u8 *)sprite + 0x2C) = direction_frames;
        func_80047784(sprite,
            direction_frames[((D_80083228[0] + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    state->count++;
    *(s32 *)((u8 *)actor + 0x1C) &= ~0x40000;
    return 1;
}
