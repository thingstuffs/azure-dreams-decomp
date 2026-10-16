/* Relink of matched dungeon/func_8125456C at file 0x127456C; imports and data use paired retail relocations. */
#define gameWork D_80084818
#include "common.h"
#include "shared/game_work.h"

extern s32 func_80047320();
extern void func_800A86C4();
extern void func_8016ABE0();

extern u8 D_8016CE94[];
extern u8 *D_8016D714;
extern u16 D_8016D718;

/* Advance the repeated command stream and apply its direction and action to the actor. */
s32 func_8016CD6C(u8 *actor, s32 action_context, u8 *sprite) {
    u8 *saved_actor;
    u8 *entry;
    s32 command;
    s32 command_byte;
    u8 *dispatch_actor;
    u8 repeat_count;
    s16 repeat_index;
    s32 command_type;

    entry = D_8016D714;
    command = entry[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        saved_actor = actor;
        saved_actor[0xBA] = 0;
        dispatch_actor = actor;
    } else {
        saved_actor = actor;

        repeat_index = D_8016D718 + 1;
        repeat_count = entry[0];
        D_8016D718 = repeat_index;
        if (repeat_count < repeat_index) {
            D_8016D714 = entry + 2;
            D_8016D718 = 0;
            saved_actor[0x9B] = 0;
        }

        *(s16 *)(saved_actor + 0x2A) = (command & 7) << 9;
        *(u16 *)(saved_actor + 0x46) |= 0x8000;

        command_type = command_byte & 0xF8;
        switch (command_type) {
        case 8:
            func_8016ABE0(saved_actor, action_context, sprite, saved_actor);
            return 0;
        case 0x10:
            if (*(u8 **)(sprite + 0x2C) != D_8016CE94) {
                *(u8 **)(sprite + 0x2C) = D_8016CE94;
                func_80047320(sprite,
                              D_8016CE94[((gameWork.view.viewAngle +
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
