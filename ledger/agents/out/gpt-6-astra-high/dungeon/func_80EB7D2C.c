#include "common.h"

typedef struct S_8017352C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    u8 * unk_A4;
    u16 unk_A8;
} S_8017352C_0;   /* arg0 in func_8017352C */

typedef struct S_8017352C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_8017352C_1;   /* arg2 in func_8017352C */

typedef struct S_8017352C_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017352C_2;   /* arg3 in func_8017352C */

typedef struct S_8017352C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017352C_3;   /* counter_base in func_8017352C */

typedef struct S_8017352C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8017352C_4;   /* global_base in func_8017352C */

typedef struct S_8017352C_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_8017352C_5;   /* part20 in func_8017352C */

typedef struct S_8017352C_6 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8017352C_6;   /* part28 in func_8017352C */

typedef struct S_8017352C_7 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017352C_7;   /* owner in func_8017352C */

typedef struct S_8017352C_8 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8017352C_8;   /* origin in func_8017352C */

typedef struct S_8017352C_9 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8017352C_9;   /* arg1 in func_8017352C */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
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
extern void func_80173D10(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801711A4[];
extern u8 D_80174184[];
extern u8 D_801741CC[];

/* Updates the actor's animation state, timers, and action transitions. */
void func_8017352C(void *in_entity, void *in_motion, void *in_sprite, void *in_actor)
{
    void *entity;
    register void *motion ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *sprite ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *actor ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *body_part;
    u8 *part_anim;
    u8 *global_base;
    u8 *body;
    register u8 *counter_base ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 actor_flags;
    s32 state;
    u16 timer;
    u16 count;

    entity = in_entity;
    motion = in_motion;
    sprite = in_sprite;
#ifndef __mips__
#endif
    body = ((S_8017352C_0 *)entity)->unk_A4;
    state = ((S_8017352C_0 *)entity)->unk_9B;
    body_part = body + 0x20;
    part_anim = body + 0x28;
#ifndef __mips__
#endif
    actor = in_actor;
#ifndef __mips__
#endif
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
    ((S_8017352C_0 *)entity)->unk_90 += 0x80000;
    if (!(((S_8017352C_1 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = D_801741CC;
    func_80047784(sprite,
        D_801741CC[((D_80083228 + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    counter_base = (u8 *)&D_80083460;
    ((S_8017352C_0 *)entity)->unk_96 = 0;
    count = ((S_8017352C_3 *)counter_base)->unk_0A - 1;
    goto store_count;

state_one:
    if ((func_80042900(actor, 1) << 16) == 0) {
        goto animate;
    }
    global_base = (u8 *)&D_80083460;
    if (((S_8017352C_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (((S_8017352C_2 *)actor)->unk_64 != 0) {
        if (func_800AA6B4(entity, motion, sprite, 0) != 0) {
            goto done;
        }
    }
    if (((S_8017352C_2 *)actor)->unk_25 == 0) {
        if (((S_8017352C_4 *)global_base)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(entity, motion, sprite, actor);
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        goto done;
    }
    actor_flags = ((S_8017352C_2 *)actor)->unk_1C.s;
    if (actor_flags & 0x100) {
        func_800AA258(entity, motion, sprite, actor);
        goto done;
    }
    if (actor_flags & 0x80000) {
        func_800AA888(entity, motion, sprite, actor);
        ((S_8017352C_0 *)entity)->unk_A8 = 0;
        func_80173D10(entity, motion, sprite, actor);
        goto done;
    }

    timer = ((S_8017352C_0 *)entity)->unk_96 - 1;
    ((S_8017352C_0 *)entity)->unk_96 = timer;
    if ((timer << 16) <= 0) {
        ((S_8017352C_5 *)body_part)->unk_04 &= 0x7FFF;
        func_80047784(part_anim, 0x27, 0);
        ((S_8017352C_0 *)entity)->unk_96 = (rand() & 0xF) + 0x20;
    }
    if (((S_8017352C_6 *)part_anim)->unk_14 & 0x6000) {
        ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
    }
    if (((S_8017352C_2 *)actor)->unk_6D == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        void *owner = D_800814A8;

        if ((func_8009A180(actor,
                (u8 *)((S_8017352C_7 *)owner)->unk_58 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if ((func_80042900(actor, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 tile = ((S_8017352C_1 *)sprite)->unk_26;

        if (((tile == ((S_8017352C_8 *)origin)->unk_26) && (tile >= 0)) ||
            ((s16)func_8009FD40(origin, sprite) < 2)) {
            if (!(func_800A6D30() & 7)) {
                func_80042B68(actor, 1);
            }
        }
    }
    if ((func_80042900(actor, 1) << 16) != 0) {
        goto done;
    }

animate:
    (*(void * *)((u8 *)sprite + 0x2C)) = D_80174184;
    func_80047784(sprite,
        D_80174184[((D_80083228 + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_8017352C_2 *)actor)->unk_1C.u |= 0x40000;
    ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
    if (((S_8017352C_1 *)sprite)->unk_14 & 0x8000) {
        goto clear_flag;
    }
    counter_base = (u8 *)3;
    ((S_8017352C_0 *)entity)->unk_96 = (s32)counter_base;
    ((S_8017352C_0 *)entity)->unk_98 &= 0xBFFF;
    counter_base = (u8 *)&D_80083460;
    count = ((S_8017352C_3 *)counter_base)->unk_0A + 1;

store_count:
    ((S_8017352C_3 *)counter_base)->unk_0A = count;
    ((S_8017352C_0 *)entity)->unk_9B++;
    goto done;

state_two:
    timer = ((S_8017352C_0 *)entity)->unk_96 - 1;
    ((S_8017352C_0 *)entity)->unk_96 = timer;
    if ((timer << 16) <= 0) {
        ((S_8017352C_0 *)entity)->unk_98 |= 0x4000;
        ((S_8017352C_9 *)motion)->unk_14 = 0xFFF80000;
    }
    if (!(((S_8017352C_1 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    counter_base = (u8 *)&D_80083460;
    ((S_8017352C_9 *)motion)->unk_14 = 0;
    ((S_8017352C_0 *)entity)->unk_A8 = 0;
    ((S_8017352C_3 *)counter_base)->unk_0A--;

clear_flag:
    ((S_8017352C_2 *)actor)->unk_1C.u &= -0x201;
    ((S_8017352C_0 *)entity)->unk_8C = D_801711A4;

done:
    return;
}
