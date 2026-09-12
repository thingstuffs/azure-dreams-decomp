#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174218(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171400[];
extern u8 D_80175140[];
extern u8 D_80175188[];
extern u8 D_80175190[];


typedef struct S_80173A2C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80173A2C_0;   /* arg0 in func_80173A2C */



typedef struct S_80173A2C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173A2C_3;   /* counter_base in func_80173A2C */

typedef struct S_80173A2C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173A2C_4;   /* global_base in func_80173A2C */

typedef struct S_80173A2C_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173A2C_5;   /* owner in func_80173A2C */

typedef struct S_80173A2C_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173A2C_6;   /* origin in func_80173A2C */


/* Updates an actor's action state and animation before restoring its default callback. */
void func_80173A2C(void *controller_in, void *motion_in, void *sprite_in, void *actor_in)
{
    void *motion;
    register void *sprite ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    s32 actor_flags;
    u16 ticks_left;
    u8 *global_base;
    s32 state;

    motion = motion_in;
    sprite = sprite_in;
    actor = actor_in;

#ifndef __mips__
#endif

    state = ((S_80173A2C_0 *)controller_in)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    ((S_80173A2C_0 *)controller_in)->unk_90 += 0x100000;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80175188;
    func_80047784(sprite,
        D_80175188[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_80173A2C_3 *)counter_base)->unk_0A--;
    }
    ((S_80173A2C_0 *)controller_in)->unk_9B++;
    goto done;

state_one:
    if ((func_80042900(actor, 1) << 16) == 0) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80175190;
        func_80047784(sprite,
            D_80175190[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 | 0x40000;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = actor_flags;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = actor_flags & ~0x200;
            goto set_callback;
        }
        goto increment_state;
    }
    global_base = (u8 *)&D_80083460;
    if (((S_80173A2C_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) {
        if (func_800AA6B4(controller_in, motion, sprite, 0) != 0) {
            goto done;
        }
    }
    if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
        if (((S_80173A2C_4 *)global_base)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(controller_in, motion, sprite, actor);
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        goto done;
    }
    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
    if (actor_flags & 0x100) {
        func_800AA258(controller_in, motion, sprite, actor);
        goto done;
    }
    if (actor_flags & 0x80000) {
        func_800AA888(controller_in, motion, sprite, actor);
        ((S_80173A2C_0 *)controller_in)->unk_A8 = 0;
        func_80174218(controller_in, motion, sprite, actor);
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        void *owner = D_800814A8;

        if ((func_8009A180(actor,
                (u8 *)((S_80173A2C_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if ((func_80042900(actor, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

        if (((tile == ((S_80173A2C_6 *)origin)->unk_26) && (tile >= 0)) ||
            ((s16)func_8009FD40(origin, sprite) < 2)) {
            if (!(func_800A6D30() & 7)) {
                func_80042B68(actor, 1);
            }
        }
    }
    if ((func_80042900(actor, 1) << 16) != 0) {
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80175190;
    func_80047784(sprite,
        D_80175190[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 | 0x40000;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = actor_flags;
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = actor_flags & ~0x200;
        goto set_callback;
    }

increment_state:
    ((S_80173A2C_0 *)controller_in)->unk_96 = 3;
    ((S_80173A2C_0 *)controller_in)->unk_98 &= 0xBFFF;
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_80173A2C_3 *)counter_base)->unk_0A++;
    }
    ((S_80173A2C_0 *)controller_in)->unk_9B++;
    goto done;

state_two:
    ticks_left = ((S_80173A2C_0 *)controller_in)->unk_96 - 1;
    ((S_80173A2C_0 *)controller_in)->unk_96 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        ((S_80173A2C_0 *)controller_in)->unk_98 |= 0x4000;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFEC0000;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((S_80173A2C_0 *)controller_in)->unk_A8 = 0;
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80175140;
    func_80047784(sprite,
        D_80175140[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_80173A2C_3 *)counter_base)->unk_0A--;
    }
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= ~0x200;

set_callback:
    ((S_80173A2C_0 *)controller_in)->unk_8C = D_80171400;

done:
    return;
}
