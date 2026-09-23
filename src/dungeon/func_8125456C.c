#include "common.h"

extern s32 func_80047784();
extern void func_800A9A0C();
extern void func_80171BE0();

extern s16 D_80083228;
extern u8 D_80173E94[];
extern u8 *D_80174714;
extern u16 D_80174718;

/* Advance the repeated command stream and apply its direction and action to the actor. */
s32 func_8125456C(u8 *actor, s32 action_context, u8 *sprite) {
    u8 *saved_actor;
    u8 *entry;
    s32 command;
    s32 command_byte;
    u8 *dispatch_actor;
    u8 repeat_count;
    s16 repeat_index;
    s32 command_type;
    s32 type_8_tag;

    entry = D_80174714;
    command = entry[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        saved_actor = actor;
        saved_actor[0xBA] = 0;
        dispatch_actor = actor;
        goto dispatch;
    }
    saved_actor = actor;

    repeat_index = D_80174718 + 1;
    repeat_count = entry[0];
    D_80174718 = repeat_index;
    if (repeat_count < repeat_index) {
        D_80174714 = entry + 2;
        D_80174718 = 0;
        saved_actor[0x9B] = 0;
    }

    type_8_tag = 8;
    *(s16 *)(saved_actor + 0x2A) = (command & 7) << 9;
    *(u16 *)(saved_actor + 0x46) |= 0x8000;

    command_type = command_byte & 0xF8;
    if (command_type == type_8_tag) {
        goto type_8;
    }
    if (command_type == 0x10) {
        goto type_10;
    }
    dispatch_actor = saved_actor;
    goto dispatch;

type_8:
    func_80171BE0(saved_actor, action_context, sprite, saved_actor);
    return 0;

type_10:
    if (*(u8 **)(sprite + 0x2C) != D_80173E94) {
        *(u8 **)(sprite + 0x2C) = D_80173E94;
        func_80047784(sprite,
                      D_80173E94[((D_80083228 +
                                   *(s16 *)(saved_actor + 0x2A) + 0x100) >> 9) & 7],
                      *(s8 *)(sprite + 4));
    }
    dispatch_actor = saved_actor;
dispatch:
    func_800A9A0C(dispatch_actor);
    return 0;
}
