#include "common.h"

extern void func_80047784();

extern u8 D_80083160[];
extern s32 D_80083460;
extern u8 D_80170E94[];
extern u8 D_80175F10[];
extern u8 D_80175F28[];

#define FIELD(type, base, offset) (*(type *)((u8 *)(base) + (offset)))

/* Updates directional animation and entity state when the transition flags allow. */
void func_801748DC(void *entity, void *unused, void *animation, void *orientation)
{
    u8 *scene_data = D_80083160;
    u16 *counters;
    u8 state = FIELD(u8, entity, 0x9B);

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    if (FIELD(u16, animation, 0x14) & 0xE000) {
        FIELD(void *, animation, 0x2C) = D_80175F28;
        func_80047784(animation,
            D_80175F28[((FIELD(s16, scene_data, 0xC8) +
                FIELD(s16, orientation, 0x2A) + 0x100) >> 9) & 7], 0);
        FIELD(u8, entity, 0x9B)++;
    }
    goto done;

state_one:
    {
        s32 scene_flags = FIELD(s32, scene_data, 8);

        if (!(scene_flags & 0x100) && (scene_flags & 0xFFFF)) {
            FIELD(void *, animation, 0x2C) = D_80175F10;
            func_80047784(animation,
                D_80175F10[((FIELD(s16, scene_data, 0xC8) +
                    FIELD(s16, orientation, 0x2A) + 0x100) >> 9) & 7], 0);
            FIELD(void *, entity, 0x8C) = D_80170E94;
            FIELD(s16, entity, 0xA6) = 0;
            counters = (u16 *)&D_80083460;
            counters[5]--;
        }
    }

done:
    return;
}

