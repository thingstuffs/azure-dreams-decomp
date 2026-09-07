#include "common.h"

extern s32 func_80047784();
extern void func_800A9A0C();
extern void func_80171BE0();
extern void func_80173E6C() __attribute__((noreturn));
extern void func_80173E78(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u8 D_80173E94[];
extern u8 *D_80174714;
extern u16 D_80174718;

/* Advance the repeated command stream and apply its direction and action to the actor. */
s32 func_8125456C(u8 *actor, s32 action_context, u8 *sprite) {
    u8 *saved_sprite = sprite;
    u8 *saved_actor;
    u8 *entry;
    register s32 command ASM_REG("$7");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 command_byte;
    u8 *dispatch_actor;
    s32 tail_zero;
    u8 repeat_count;
    s16 repeat_index;
    s32 command_type;
    s32 type_8_tag;

    entry = D_80174714;
    command = entry[1];
    command_byte = command & 0xFF;
    ASM_KEEP_NV(command_byte);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (command_byte == 0) {
        saved_actor = actor;
        ASM_KEEP(saved_actor);   /* MATCH pin: load-bearing for the whole function shape */
        saved_actor[0xBA] = 0;
        func_80173E6C();
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
    ASM_KEEP(dispatch_actor);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173E6C();

type_8:
    func_80171BE0(saved_actor, action_context, saved_sprite, saved_actor);
    tail_zero = 0;
    ASM_TAILSLOT_PIN_TIED(tail_zero);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80173E78();

type_10:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    if (*(u8 **)(saved_sprite + 0x2C) != D_80173E94) {
        *(u8 **)(saved_sprite + 0x2C) = D_80173E94;
        func_80047784(saved_sprite,
                      D_80173E94[((D_80083228 +
                                   *(s16 *)(saved_actor + 0x2A) + 0x100) >> 9) & 7],
                      *(s8 *)(saved_sprite + 4), command);
    }
    dispatch_actor = saved_actor;
    ASM_KEEP(dispatch_actor);   /* MATCH pin: retail delay-slot contents depend on it */
    func_800A9A0C(dispatch_actor);
    return 0;
}
