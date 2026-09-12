#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    u16 unk_A0;
} S_8017357C_0;   /* arg0 in func_8017357C */



typedef struct S_8017357C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017357C_3;   /* counter_base in func_8017357C */

typedef struct S_8017357C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8017357C_4;   /* global_base in func_8017357C */

typedef struct S_8017357C_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017357C_5;   /* owner in func_8017357C */

typedef struct S_8017357C_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8017357C_6;   /* origin in func_8017357C */




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
extern void func_80173D38(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174AFC[];
extern u8 D_80174B04[];

/* Updates actor state, animation, and transition counters. */
void func_8017357C(void *controller, void *motion, void *sprite, void *actor)
{
    s32 actor_flags;
    u8 *global_base;
    s32 state;

    state = ((S_8017357C_0 *)controller)->unk_9B;
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
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AFC;
    func_80047784(sprite,
        D_80174AFC[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_8017357C_3 *)(u8 *)&D_80083460)->unk_0A = ((S_8017357C_3 *)(u8 *)&D_80083460)->unk_0A - 1;
    ((S_8017357C_0 *)controller)->unk_9B++;
    goto done;

state_one:
    if ((func_80042900(actor, 1) << 16) == 0) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174B04;
        func_80047784(sprite,
            D_80174B04[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
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
    if (((S_8017357C_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) {
        if (func_800AA6B4(controller, motion, sprite, 0) != 0) {
            goto done;
        }
    }
    if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
        if (((S_8017357C_4 *)global_base)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(controller, motion, sprite, actor);
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        goto done;
    }
    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
    if (actor_flags & 0x100) {
        func_800AA258(controller, motion, sprite, actor);
        goto done;
    }
    if (actor_flags & 0x80000) {
        func_800AA888(controller, motion, sprite, actor);
        ((S_8017357C_0 *)controller)->unk_A0 = 0;
        func_80173D38(controller, motion, sprite, actor);
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        void *owner = D_800814A8;

        if ((func_8009A180(actor,
                (u8 *)((S_8017357C_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if ((func_80042900(actor, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

        if (((tile == ((S_8017357C_6 *)origin)->unk_26) && (tile >= 0)) ||
            ((s16)func_8009FD40(origin, sprite) < 2)) {
            if (!(func_800A6D30() & 7)) {
                func_80042B68(actor, 1);
            }
        }
    }
    if ((func_80042900(actor, 1) << 16) != 0) {
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80174B04;
    func_80047784(sprite,
        D_80174B04[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 | 0x40000;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = actor_flags;
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = actor_flags & ~0x200;
        goto set_callback;
    }

increment_state:
    ((S_8017357C_0 *)controller)->unk_96.s = 3;

    ((S_8017357C_3 *)(u8 *)&D_80083460)->unk_0A = ((S_8017357C_3 *)(u8 *)&D_80083460)->unk_0A + 1;
    ((S_8017357C_0 *)controller)->unk_9B++;
    goto done;

state_two:
    ((S_8017357C_0 *)controller)->unk_96.s--;
    if (((S_8017357C_0 *)controller)->unk_96.u <= 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFF00000;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((S_8017357C_0 *)controller)->unk_A0 = 0;
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
    func_80047784(sprite,
        D_80174AD4[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_8017357C_3 *)counter_base)->unk_0A--;
    }
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= ~0x200;

set_callback:
    ((S_8017357C_0 *)controller)->unk_8C = D_80171138;

done:
    return;
}
