#include "common.h"

typedef struct {
    u8 pad_00[0x8C];
    void *field_8C;
    u8 pad_90[6];
    u16 field_96;
    u16 field_98;
    u8 pad_9A;
    u8 state;
} D0;

typedef struct {
    u8 pad_00[4];
    s8 kind;
    u8 pad_05[0x0F];
    u16 flags;
    u8 pad_16[0x0E];
    u8 value_24;
    u8 value_25;
    u8 pad_26[6];
    void *field_2C;
} D2;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
    u8 pad_18[0x12];
    s16 value_2A;
    u8 pad_2C[0x1A];
    u16 value_46;
    u8 pad_48[0x18];
    void *field_60;
} D3;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
} D3Nested;

extern u8 D_80171094[];
extern s32 D_8008346C[];
extern u8 D_80176460[8];
extern s16 D_80083228[5];

extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(D3 *, s32);
extern void func_80047784(D2 *, u8, s32);
extern void func_80175F60(D0 *, void *, D2 *);
extern void func_801762A4(s32, D3 *);

/* Advances a timed actor state sequence and updates its sprite direction. */
void func_80174D2C(D0 *action, void *context, D2 *sprite, D3 *actor) {
    s32 action_state;
    u16 sprite_flags;
    u16 ticks_left;

    action_state = action->state;
    if (action_state == 1) {
        goto state_1;
    }
    if (action_state < 2) {
        if (action_state == 0) {
            goto state_0;
        }
    } else if (action_state == 2) {
        goto state_2;
    }
    goto common;

state_0:
    sprite_flags = sprite->flags;
    if (sprite_flags & 0x8000) {
        sprite->flags = sprite_flags | 0x6000;
        action->state = 2;
        goto epilogue;
    }
    if (sprite->kind == 1) {
        if (sprite_flags & 0x1000) {
            goto call_75f60;
        }
        if ((sprite_flags & 0x6000) == 0) {
            goto common;
        }
    } else {
        if ((sprite_flags & 0x6000) == 0) {
            goto common;
        }
    }

call_75f60:
    func_80175F60(action, context, sprite);
    if (actor->flags & 0x4000) {
        func_801762A4(1, actor);
    } else if (((D3Nested *) actor->field_60)->flags & 0x4000) {
        func_801762A4(0, actor);
    }
    func_800A56E0(0x80D);
    action->field_96 = 0x20;
    action->state = action->state + 1;
    goto common;

state_1:
    ticks_left = action->field_96 - 1;
    action->field_96 = ticks_left;
    if ((ticks_left << 16) != 0) {
        if (!(sprite->flags & 0x8000)) {
            goto common;
        }
    }
    action->field_96 = 4;
    action->state = action->state + 1;
    goto common;

state_2:
    ticks_left = action->field_96 - 1;
    action->field_96 = ticks_left;
    if ((ticks_left << 16) != 0) {
        if (!(sprite->flags & 0xE000)) {
            goto epilogue;
        }
    }
    func_800AD594(actor, 0x400);
    func_800A2B04(context, sprite->value_24, sprite->value_25);
    action->field_8C = D_80171094;
    *D_8008346C = 0;
    actor->value_46 &= 0x7FFF;

common:
    if (sprite->flags & 0xE000) {
        sprite->field_2C = D_80176460;
        func_80047784(sprite, D_80176460[(((*D_80083228 + actor->value_2A + 0x100) >> 9) & 7)], 0);
        action->field_98 &= 0xFFF7;
    }

epilogue:
    return;
}
