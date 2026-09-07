#include "common.h"

typedef struct S_801724F4_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_801724F4_0;   /* arg3 in func_801724F4 */

typedef struct S_801724F4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801724F4_1;   /* arg0 in func_801724F4 */

typedef struct S_801724F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801724F4_2;   /* arg2 in func_801724F4 */

typedef struct S_801724F4_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_801724F4_3;   /* arg1 in func_801724F4 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_801711A4;
extern u8 D_8017419C[];
extern u8 D_801741A4[];

/* Updates directional movement and animation, then settles the actor on its destination tile. */
void func_801724F4(void *action, void *motion, void *sprite, void *actor)
{
    s32 dir_x;
    s32 dir_y;
    s32 dir_offset;
    s32 ticks_left;
    s32 state;

    dir_offset = ((u16)((S_801724F4_0 *)actor)->unk_2A.s >> 8) & 0xE;
    dir_x = *(s16 *)((u8 *)&D_8006CCD8 + dir_offset);
    dir_y = *(s16 *)((u8 *)&D_8006CCE8 + dir_offset);
    state = ((S_801724F4_1 *)action)->unk_9B;
    ticks_left = ((S_801724F4_1 *)action)->unk_96 - 1;
    ((S_801724F4_1 *)action)->unk_96 = ticks_left;

    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_zero:
    if (((S_801724F4_2 *)sprite)->unk_14 & 0x8000) {
        ((S_801724F4_1 *)action)->unk_9B = 0xFF;
        ((S_801724F4_2 *)sprite)->unk_14 |= 0x6000;
        func_8009C12C(actor, sprite, ((S_801724F4_0 *)actor)->unk_2A.u, 1);
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_8017419C;
    func_80047784(sprite,
        D_8017419C[((D_80083228 + ((S_801724F4_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    goto increment_state;

state_one:
    if (((S_801724F4_2 *)sprite)->unk_14 & 0xE000) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_801741A4;
        func_80047784(sprite,
            D_801741A4[((D_80083228 + ((S_801724F4_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
            0);
        ((S_801724F4_3 *)motion)->unk_0C = (dir_x << 18) + (dir_x << 17);
        ((S_801724F4_3 *)motion)->unk_10 = (dir_y << 18) + (dir_y << 17);
        ((S_801724F4_1 *)action)->unk_96 = 8;
        func_800A56E0(0x607);
increment_state:
        ((S_801724F4_1 *)action)->unk_9B++;
    }
    goto done;

state_two:
    if ((ticks_left << 16) <= 0) {
        func_8009C12C(actor, sprite, ((S_801724F4_0 *)actor)->unk_2A.u, 1);
        ((S_801724F4_1 *)action)->unk_9B = 0xFF;
    }
    goto done;

state_ff:
    {
        s32 target_x = ((S_801724F4_2 *)sprite)->unk_24 << 6;
        s32 current_x = ((S_801724F4_3 *)motion)->unk_02 - 0x20;
        ((S_801724F4_3 *)motion)->unk_0C = ((target_x - current_x) << 0xF) >> 1;
    }
    {
        s32 target_y = ((S_801724F4_2 *)sprite)->unk_25 << 6;
        s32 current_y = ((S_801724F4_3 *)motion)->unk_06 - 0x20;
        ((S_801724F4_3 *)motion)->unk_10 = ((target_y - current_y) << 0xF) >> 1;
    }
    if (((S_801724F4_2 *)sprite)->unk_14 & 0xE000) {
        ((S_801724F4_3 *)motion)->unk_10 = 0;
        ((S_801724F4_3 *)motion)->unk_0C = 0;
        ((S_801724F4_0 *)actor)->unk_1C |= 0x40000;
        func_800A2B04(motion, ((S_801724F4_2 *)sprite)->unk_24, ((S_801724F4_2 *)sprite)->unk_25);
        func_800AD594(actor, 0x100);
        ((S_801724F4_1 *)action)->unk_8C = &D_801711A4;
        D_8008346C = 0;
        func_800A4ACC(actor);
        if (((S_801724F4_0 *)actor)->unk_6D == 0) {
            ((S_801724F4_0 *)actor)->unk_46 &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)actor - 0x20;
        }
    }

done:
    return;
}
