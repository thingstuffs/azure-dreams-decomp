#include "engine/graphics/select_sprite_entry_api.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/monster/beldo/command_ticks_data.h"
#include "dungeon/data.h"

#include "dungeon/actor/state.h"

extern void func_80171BE0(); /* Slot contract: loading images do not establish one callee contract. */

extern u8 *beldo_effect_stream;

/* Advance the repeated command stream and apply its direction and action to the actor. */
s32 replay_actor_direction_commands(ActorRecord *actor, ObjectPosition *action_context, SpriteFrameState *sprite) {
    ActorRecord *saved_actor;
    u8 *entry;
    s32 command;
    s32 command_byte;
    ActorRecord *dispatch_actor;
    u8 repeat_count;
    s16 repeat_index;
    s32 command_type;

    entry = beldo_effect_stream;
    command = entry[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        saved_actor = actor;
        saved_actor->unk_BA = 0;
        dispatch_actor = actor;
    } else {
        saved_actor = actor;

        repeat_index = beldo_command_ticks + 1;
        repeat_count = entry[0];
        beldo_command_ticks = repeat_index;
        if (repeat_count < repeat_index) {
            beldo_effect_stream = entry + 2;
            beldo_command_ticks = 0;
            saved_actor->action_phase = 0;
        }

        saved_actor->facing = (command & 7) << 9;
        saved_actor->action_flags |= 0x8000;

        command_type = command_byte & 0xF8;
        switch (command_type) {
        case 8:
            func_80171BE0(saved_actor, action_context, sprite, saved_actor);
            return 0;
        case 0x10:
            if (*(u8 **)&sprite->frameTable != beldo_frame_set_2) {
                sprite->frameTable = beldo_frame_set_2;
                select_sprite_entry(sprite,
                              beldo_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle +
                                           saved_actor->facing + 0x100) >> 9) & 7],
                              sprite->unk_04);
            }
            break;
        }
        dispatch_actor = saved_actor;
    }
    update_actor_status_and_mp(dispatch_actor);
    return 0;
}
