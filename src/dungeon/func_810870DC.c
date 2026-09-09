#include "common.h"

extern void func_80047784();

extern u8 D_80083160[];
extern s32 D_80083460;
extern u8 D_80170E94[];
extern u8 D_80175F10[];
extern u8 D_80175F28[];

typedef struct S_func_810870DC_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
} S_func_810870DC_0;

typedef struct S_func_810870DC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    void *unk_2C;
} S_func_810870DC_1;

typedef struct S_func_810870DC_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_func_810870DC_2;

typedef struct S_func_810870DC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_func_810870DC_3;

/* Updates directional animation and entity state when the transition flags allow. */
void func_801748DC(S_func_810870DC_0 *entity, void *unused, S_func_810870DC_1 *animation, S_func_810870DC_2 *orientation)
{
    S_func_810870DC_3 *scene_data = (S_func_810870DC_3 *)D_80083160;
    u16 *counters;
    u8 state = entity->unk_9B;

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    if (animation->unk_14 & 0xE000) {
        animation->unk_2C = D_80175F28;
        func_80047784(animation,
            D_80175F28[((scene_data->unk_C8 +
                orientation->unk_2A + 0x100) >> 9) & 7], 0);
        entity->unk_9B++;
    }
    goto done;

state_one:
    {
        s32 scene_flags = scene_data->unk_08;

        if (!(scene_flags & 0x100) && (scene_flags & 0xFFFF)) {
            animation->unk_2C = D_80175F10;
            func_80047784(animation,
                D_80175F10[((scene_data->unk_C8 +
                    orientation->unk_2A + 0x100) >> 9) & 7], 0);
            entity->unk_8C = D_80170E94;
            entity->unk_A6 = 0;
            counters = (u16 *)&D_80083460;
            counters[5]--;
        }
    }

done:
    return;
}

