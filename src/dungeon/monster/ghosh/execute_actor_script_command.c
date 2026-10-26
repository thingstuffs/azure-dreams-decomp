#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"

typedef struct S_8016EF10_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x40];
    s16 unk_88;
    u8 pad_8A[0xC];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x16];
    u8 unk_B2;
} S_8016EF10_1;   /* actor in execute_actor_script_command */

extern s32 update_actor_status_and_mp();
extern void * create_five_point_effect();
extern s32 func_8016A928();
extern s32 advance_actor_path();

extern u8 D_800DF45C[];
extern u8 D_8016EEBC[];
extern u8 ghosh_frame_set_3[];
extern u8 ghosh_frame_set_9[];
extern u8 ghosh_frame_set_13[];
extern u8 *ghosh_script_cursor[];
extern s16 ghosh_script_repeat_count[];

/* Executes the current actor script command and advances its repeat counter. */
s32 execute_actor_script_command(u8 *actor_arg, s32 action_context, u8 *entity_arg) {
    u8 *actor = actor_arg;
    SpriteFrameState *entity= entity_arg;
    u8 *command_stream;
    u16 command;
    s32 command_wide;
    u8 repeat_limit;
    s16 repeat_count;
    s32 opcode;
    s32 direction_index;

    if (entity->flags & 0x40) {
        return 0;
    }

    command_stream = ghosh_script_cursor[0];
    command = command_stream[1];
    command_wide = command;
    if (command_wide == 0) {
        ((S_8016EF10_1 *)actor)->unk_B2 = 0;
        update_actor_status_and_mp(actor);
        return 0;
    }

    repeat_limit = command_stream[0];
    repeat_count = ghosh_script_repeat_count[0] + 1;
    ghosh_script_repeat_count[0] = repeat_count;
    if (repeat_limit < repeat_count) {
        ghosh_script_cursor[0] = command_stream + 2;
        ghosh_script_repeat_count[0] = 0;
    }

    ((S_8016EF10_1 *)actor)->unk_2A = (command & 7) << 9;
    ((S_8016EF10_1 *)actor)->unk_46 |= 0x8000;
    opcode = command_wide & 0xF8;

    switch (opcode) {
    default:
        update_actor_status_and_mp(actor);
        return 0;

    case 8:
        advance_actor_path(actor, action_context, entity, actor);
        return 0;

    case 0x10:
        if (*(u8 **)&entity->frameTable != ghosh_frame_set_3) {
            entity->frameTable = ghosh_frame_set_3;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016EF10_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
            select_sprite_entry(entity, ghosh_frame_set_3[direction_index], 0);
        }
        break;

    case 0xF8:
        if (*(u8 **)&entity->frameTable != ghosh_frame_set_13) {
            entity->frameTable = ghosh_frame_set_13;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016EF10_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
            select_sprite_entry(entity, ghosh_frame_set_13[direction_index], 0);
        }
        break;

    case 0xF0:
        if (((S_8016EF10_1 *)actor)->unk_9B == 0) {
            ((S_8016EF10_1 *)actor)->unk_2A = func_8016A928(action_context) << 9;
            if (*(u8 **)&entity->frameTable != ghosh_frame_set_9) {
                entity->frameTable = ghosh_frame_set_9;
                direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016EF10_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
                select_sprite_entry(entity, ghosh_frame_set_9[direction_index], 0);
            }
            if (create_five_point_effect(entity->tile_x,
                              entity->tile_y,
                              ((S_8016EF10_1 *)actor)->unk_88,
                              D_800DF45C, 0x2800, 0x208020,
                              D_8016EEBC) == 0) {
                return 0;
            }
            ((S_8016EF10_1 *)actor)->unk_96 = 0;
            ((S_8016EF10_1 *)actor)->unk_9B++;
            {
                g_dungeon_status.activity_counts.parts.pending_action_count += 2;
            }
        }
        break;

    }

    update_actor_status_and_mp(actor);
    return 0;
}
