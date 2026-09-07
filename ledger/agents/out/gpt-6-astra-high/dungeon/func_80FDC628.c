#include "common.h"

typedef struct {
    u8 pad_00[0x84];
    u8 field_84;
    u8 field_85;
    u8 pad_86[0x06];
    s32 field_8c;
    u8 pad_90[0x08];
    u16 field_98;
    s8 field_9a;
    s8 field_9b;
    u8 pad_9c[0x10];
    u8 field_ac;
} Arg0;

typedef struct {
    u8 pad_00[0x03];
    u8 field_03;
    u8 pad_04[0x18];
    s32 field_1c;
    u8 pad_20[0x0a];
    s16 field_2a;
    u8 pad_2c[0x1a];
    u16 field_46;
    u8 pad_48[0x24];
    u8 field_6c;
    u8 field_6d;
    u8 pad_6e[0x03];
    u8 field_71;
    u8 pad_72[0x12];
    u8 field_84;
    u8 field_85;
} Arg3;

typedef struct {
    u8 pad_00[0x24];
    u8 field_24;
    u8 field_25;
    u8 pad_26[0x06];
    u8 *field_2c;
} Arg2;

typedef struct {
    u8 pad_00[0x02];
    u16 flags;
    u8 pad_04[0x08];
} Global83460;

extern Global83460 D_80083460;
extern u16 D_80083462[5];
extern u8 D_80174038[];
extern s16 D_80083228[5];

extern s32 func_80047784(void *, u8, s32);
extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

/* Validates the actor's direction and state, then initializes its action and animation. */
s32 func_80171E28(Arg0 *action_state, s32 action_id, Arg2 *sprite, Arg3 *actor) {
    Global83460 *flags_base;
    u8 *direction_frames;
    u16 flags;
    s32 target_angle;
    s32 result;

    actor->field_71 &= 0x7F;
    flags_base = (Global83460 *)((u8 *)D_80083462 - 2);
    result = 0;
    if (flags_base->flags & 0x2000) {
        return -1;
    }

    target_angle = func_800A04F0(actor, sprite->field_24, sprite->field_25, actor->field_2a);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return result;
    }

    flags = flags_base->flags;
    if (flags & 0x2000) {
        return -1;
    }
    if ((actor->field_46 & 0x8000) == 0 && (flags & 8) != 0) {
        return -1;
    }

    if ((u32)((0 - func_800A0134(target_angle, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return result;
    }
    result = 1;
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    action_state->field_9b = 0;
    action_state->field_8c = 0;
    if (action_state->field_98 & 0x8000) {
        action_state->field_9a = 0x17;
        if (actor->field_1c & 0x1000) {
            action_state->field_98 |= 0x4000;
        } else {
            action_state->field_98 &= 0xBFFF;
        }
        action_state->field_ac = actor->field_03;
        actor->field_03 = 0xFF;
        actor->field_84 = 0x7E;
    } else {
        action_state->field_9a = 0x11;
        actor->field_84 = 0x7C;
    }
    actor->field_85 = 8;
    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */

    direction_frames = D_80174038;
    sprite->field_2c = direction_frames;
    func_80047784(sprite, direction_frames[(((s32)D_80083228[0] + actor->field_2a + 0x100) >> 9) & 7], 0);
    actor->field_6d--;
    func_8009C93C(actor, sprite, actor->field_2a, 1, 0);
    if ((action_state->field_98 & 0x8000) == 0) {
        actor->field_1c &= 0xFEFFFFFF;
    }
    return result;
}
