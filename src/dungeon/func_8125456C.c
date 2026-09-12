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
    u8 *saved_actor;
    u8 *entry;
    register s32 command ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 command_byte;
    u8 *dispatch_actor;
    s32 tail_zero;
    u8 repeat_count;
    s16 repeat_index;
    s32 command_type;
    s32 type_8_tag;

    entry = D_80174714;
    command = entry[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        saved_actor = actor;
        ASM_KEEP(saved_actor);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
    ASM_KEEP(dispatch_actor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80173E6C();

type_8:
    func_80171BE0(saved_actor, action_context, sprite, saved_actor);
    tail_zero = 0;
    ASM_TAILSLOT_PIN_TIED(tail_zero);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80173E78();

type_10:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (*(u8 **)(sprite + 0x2C) != D_80173E94) {
        *(u8 **)(sprite + 0x2C) = D_80173E94;
        func_80047784(sprite,
                      D_80173E94[((D_80083228 +
                                   *(s16 *)(saved_actor + 0x2A) + 0x100) >> 9) & 7],
                      *(s8 *)(sprite + 4), command);
    }
    dispatch_actor = saved_actor;
    ASM_KEEP(dispatch_actor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_800A9A0C(dispatch_actor);
    return 0;
}
