#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8017313C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017313C_0;   /* arg0 in func_8017313C */

typedef struct S_8017313C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    union { void * s; u8 * u; } unk_2C;   /* accessed as both */
} S_8017313C_1;   /* arg2 in func_8017313C */


typedef struct S_8017313C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017313C_3;   /* counter_base in func_8017313C */

typedef struct S_8017313C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8017313C_4;   /* global_base in func_8017313C */

typedef struct S_8017313C_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017313C_5;   /* owner in func_8017313C */

typedef struct S_8017313C_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8017313C_6;   /* origin in func_8017313C */



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
extern void func_801737C4(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E9C[];
extern u8 D_80174F00[];

/* Updates entity dimming, status behavior, and brightness recovery. */
void func_8017313C(S_8017313C_0 *controller, void *context, S_8017313C_1 *sprite, Rec_D_800E3D7C *entity)
{
    s32 entity_flags;
    u16 fade_ticks;
    u8 *global_base;
    s32 state;
    u8 shade;

    state = controller->unk_9B;
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
    shade = sprite->unk_0E - 0xC;
    sprite->unk_0E = shade;
    sprite->unk_0D = shade;
    sprite->unk_0C = shade;
    if (!(sprite->unk_14 & 0xE000)) {
        goto done;
    }
    sprite->unk_2C.s = D_80174F00;
    sprite->unk_0E = 0x40;
    sprite->unk_0D = 0x40;
    sprite->unk_0C = 0x40;
    func_80047784(sprite,
        sprite->unk_2C.u[
            ((D_80083228 + entity->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_8017313C_3 *)counter_base)->unk_0A--;
    }
    {
        u8 next_state = controller->unk_9B + 1;

        controller->unk_9B = next_state;
        goto done;
    }

state_one:
    if ((func_80042900(entity, 1) << 16) == 0) {
        if (sprite->unk_14 & 0x8000) {
            s32 cleared_flags;

            sprite->unk_0E = 0x80;
            sprite->unk_0D = 0x80;
            sprite->unk_0C = 0x80;
            cleared_flags = entity->unk_1C.as_s32 & 0xEFFFFFFF;
            entity->unk_1C.as_s32 = cleared_flags & ~0x200;
            controller->unk_8C = D_80170E9C;
            goto done;
        }
        goto advance_state_one;
    }
    global_base = (u8 *)&D_80083460;
    if (((S_8017313C_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (entity->unk_64.as_s16 != 0) {
        if (func_800AA6B4(controller, context, sprite, 0) != 0) {
            goto done;
        }
    }
    if (entity->unk_24.at01_u8.v == 0) {
        if (((S_8017313C_4 *)global_base)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(controller, context, sprite, entity);
        goto done;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        goto done;
    }
    entity_flags = entity->unk_1C.as_s32;
    if (entity_flags & 0x100) {
        func_800AA258(controller, context, sprite, entity);
        goto done;
    }
    if (entity_flags & 0x80000) {
        func_800AA888(controller, context, sprite, entity);
        func_801737C4(controller, context, sprite, entity);
        goto done;
    }
    if (entity->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        S_8017313C_5 *owner = D_800814A8;

        if ((func_8009A180(entity,
                (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(entity);
    func_800A9A04(entity);
    if ((func_80042900(entity, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 tile = sprite->unk_26;

        if (((tile == ((S_8017313C_6 *)origin)->unk_26) && (tile >= 0)) ||
            ((s16)func_8009FD40(origin, sprite) < 2)) {
            if (!(func_800A6D30() & 7)) {
                func_80042B68(entity, 1);
            }
        }
    }
    if ((func_80042900(entity, 1) << 16) != 0) {
        goto done;
    }

    if (sprite->unk_14 & 0x8000) {
        s32 cleared_flags;

        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        cleared_flags = entity->unk_1C.as_s32 & 0xEFFFFFFF;
        entity->unk_1C.as_s32 = cleared_flags & ~0x200;
        controller->unk_8C = D_80170E9C;
        goto done;
    }

advance_state_one:
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_8017313C_3 *)counter_base)->unk_0A++;
    }
    controller->unk_96 = 6;
    {
        u8 next_state = controller->unk_9B + 1;

        controller->unk_9B = next_state;
        goto done;
    }

state_two:
    {
        s32 cleared_flags;

        shade = sprite->unk_0E + 0xC;
        sprite->unk_0E = shade;
        sprite->unk_0D = shade;
        sprite->unk_0C = shade;
        fade_ticks = controller->unk_96 - 1;
        controller->unk_96 = fade_ticks;
        if ((fade_ticks << 16) > 0) {
            goto done;
        }
        {
            u8 *counter_base = (u8 *)&D_80083460;

            ((S_8017313C_3 *)counter_base)->unk_0A--;
        }
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        cleared_flags = entity->unk_1C.as_s32 & 0xEFFFFFFF;
        entity->unk_1C.as_s32 = cleared_flags & ~0x200;
        controller->unk_8C = D_80170E9C;
    }

done:
    return;
}
