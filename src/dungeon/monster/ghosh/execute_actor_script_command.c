#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"
#include "dungeon/effect/screen.h"
#include "dungeon/item.h"


extern void update_actor_status_and_mp();

extern u8 D_800DF45C[];
extern u8 D_8016EEBC[];
extern u8 ghosh_frame_set_3[];
extern u8 ghosh_frame_set_9[];
extern u8 ghosh_frame_set_13[];

/* Executes the current actor script command and advances its repeat counter. */
s32 execute_actor_script_command(ActorRecord *actor_arg, ObjectPosition *action_context, SpriteFrameState *sprite_arg) {
    ActorRecord *actor = actor_arg;
    SpriteFrameState *sprite= sprite_arg;
    u8 *command_stream;
    u16 command;
    s32 command_wide;
    u8 repeat_limit;
    s16 repeat_count;
    s32 opcode;
    s32 direction_index;

    if (sprite->flags & 0x40) {
        return 0;
    }

    command_stream = ghosh_script_cursor;
    command = command_stream[1];
    command_wide = command;
    if (command_wide == 0) {
        actor->unk_B0.bytes[2] = 0;
        update_actor_status_and_mp(actor);
        return 0;
    }

    repeat_limit = command_stream[0];
    repeat_count = ghosh_script_repeat_count + 1;
    ghosh_script_repeat_count = repeat_count;
    if (repeat_limit < repeat_count) {
        ghosh_script_cursor = command_stream + 2;
        ghosh_script_repeat_count = 0;
    }

    actor->facing = (command & 7) << 9;
    actor->action_flags |= 0x8000;
    opcode = command_wide & 0xF8;

    switch (opcode) {
    default:
        update_actor_status_and_mp(actor);
        return 0;

    case 8:
        advance_actor_path(actor, action_context, sprite, actor);
        return 0;

    case 0x10:
        if (*(u8 **)&sprite->frameTable != ghosh_frame_set_3) {
            sprite->frameTable = ghosh_frame_set_3;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, ghosh_frame_set_3[direction_index], 0);
        }
        break;

    case 0xF8:
        if (*(u8 **)&sprite->frameTable != ghosh_frame_set_13) {
            sprite->frameTable = ghosh_frame_set_13;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, ghosh_frame_set_13[direction_index], 0);
        }
        break;

    case 0xF0:
        if (actor->action_phase.u == 0) {
            actor->facing = get_direction_toward_target_position(action_context) << 9;
            if (*(u8 **)&sprite->frameTable != ghosh_frame_set_9) {
                sprite->frameTable = ghosh_frame_set_9;
                direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, ghosh_frame_set_9[direction_index], 0);
            }
            if (create_five_point_effect(sprite->tile_x,
                              sprite->tile_y,
                              actor->ground_height,
                              D_800DF45C, 0x2800, 0x208020,
                              D_8016EEBC) == 0) {
                return 0;
            }
            actor->action_timer.s = 0;
            actor->action_phase.u++;
            {
                g_dungeon_status.activity_counts.parts.pending_action_count += 2;
            }
        }
        break;

    }

    update_actor_status_and_mp(actor);
    return 0;
}
