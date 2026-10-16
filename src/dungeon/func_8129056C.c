/* Relink of matched dungeon/func_8125456C at file 0x127456C; imports and data use paired retail relocations. */
#define gameWork D_80084818
#include "common.h"
#include "shared/game_work.h"

extern s32 func_80047320();
extern void func_800A86C4();
extern void func_8015EBE0();

extern u8 D_80160E94[];
extern u8 *D_80161714;
extern u16 D_80161718;

/* Advance the repeated command stream and apply its direction and action to the actor. */
s32 func_80160D6C(u8 *actor, s32 action_context, u8 *sprite) {
    u8 *saved_actor;
    u8 *entry;
    s32 command;
    s32 command_byte;
    u8 *dispatch_actor;
    u8 repeat_count;
    s16 repeat_index;
    s32 command_type;

    entry = D_80161714;
    command = entry[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        saved_actor = actor;
        saved_actor[0xBA] = 0;
        dispatch_actor = actor;
    } else {
        saved_actor = actor;

        repeat_index = D_80161718 + 1;
        repeat_count = entry[0];
        D_80161718 = repeat_index;
        if (repeat_count < repeat_index) {
            D_80161714 = entry + 2;
            D_80161718 = 0;
            saved_actor[0x9B] = 0;
        }

        *(s16 *)(saved_actor + 0x2A) = (command & 7) << 9;
        *(u16 *)(saved_actor + 0x46) |= 0x8000;

        command_type = command_byte & 0xF8;
        switch (command_type) {
        case 8:
            func_8015EBE0(saved_actor, action_context, sprite, saved_actor);
            return 0;
        case 0x10:
            if (*(u8 **)(sprite + 0x2C) != D_80160E94) {
                *(u8 **)(sprite + 0x2C) = D_80160E94;
                func_80047320(sprite,
                              D_80160E94[((gameWork.view.viewAngle +
                                           *(s16 *)(saved_actor + 0x2A) + 0x100) >> 9) & 7],
                              *(s8 *)(sprite + 4));
            }
            break;
        }
        dispatch_actor = saved_actor;
    }
    func_800A86C4(dispatch_actor);
    return 0;
}
