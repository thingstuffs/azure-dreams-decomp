#include "common.h"

typedef struct S_801726A4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801726A4_0;   /* arg0 in func_801726A4 */

typedef struct S_801726A4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801726A4_1;   /* arg2 in func_801726A4 */

typedef struct S_801726A4_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801726A4_2;   /* arg3 in func_801726A4 */

typedef struct S_801726A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801726A4_3;   /* arg1 in func_801726A4 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174690(void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170EE4[];
extern u8 D_80176600[];
extern u8 D_80176668[];

/* Advances an actor's animation sequence and handles its completion. */
void func_801726A4(void *action, void *motion, void *sprite, void *actor)
{
    u16 sprite_flags;
    u16 frame_count;
    s32 state;

    state = ((S_801726A4_0 *)action)->unk_9B;
    if (state != 1) {
        if ((s32)state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            return;
        }

        if (state == 2) {
            goto state_two;
        }
        if (state == 3) {
            goto state_three;
        }
        return;
    }
    goto state_one;

state_zero:
    ((S_801726A4_0 *)action)->unk_98 |= 1;
    ((S_801726A4_0 *)action)->unk_9B++;

state_one:
    sprite_flags = ((S_801726A4_1 *)sprite)->unk_14;
    if (sprite_flags & 0x8000) {
        ((S_801726A4_0 *)action)->unk_9B = 3;
        ((S_801726A4_1 *)sprite)->unk_14 |= 0x6000;
        func_8009C12C(actor, sprite, ((S_801726A4_2 *)actor)->unk_2A, 1);
        return;
    }

    if (sprite_flags & 0x6000) {
        ((S_801726A4_3 *)motion)->unk_0C =
            ((S_801726A4_3 *)motion)->unk_10 =
            ((S_801726A4_3 *)motion)->unk_14 = 0;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80176600;
        func_80047784(sprite,
            D_80176600[((D_80083228 + ((S_801726A4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_80174690((u8 *)action - 0x20);
        ((S_801726A4_0 *)action)->unk_96 = 0;
        ((S_801726A4_0 *)action)->unk_9B++;
        func_800A56E0(0x804);
        return;
    }
    return;

state_two:
    frame_count = ((S_801726A4_0 *)action)->unk_96 + 1;
    ((S_801726A4_0 *)action)->unk_96 = frame_count;

    if ((s16)frame_count == state ||
        (((S_801726A4_1 *)sprite)->unk_14 & 0x8000)) {
        func_8009C12C(actor, sprite, ((S_801726A4_2 *)actor)->unk_2A, 1);
    }

    if (((S_801726A4_1 *)sprite)->unk_14 & 0xE000) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80176668;
        func_80047784(sprite,
            D_80176668[((D_80083228 + ((S_801726A4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801726A4_0 *)action)->unk_9B++;
        ((S_801726A4_0 *)action)->unk_98 &= 0xFFFE;
        return;
    }
    return;

state_three:
    if (((S_801726A4_1 *)sprite)->unk_14 & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_801726A4_0 *)action)->unk_8C = D_80170EE4;
        D_8008346C = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A4ACC(actor);
    }
}
