#include "common.h"
#include "slus.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "dungeon/player/position.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

extern u8 destination_motion_resume_address[];
extern u8 actor_default_frames[];

extern s32 classify_adjacent_tile_height();

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Moves the actor and updates its animation, movement state, and map flags. */
void update_actor_movement_and_map_flags(ActorRecord *obj, ObjectPosition *move_mode, SpriteFrameState *actor, ActorRecord *map)
{
    GameWork *globals;
    register s16 movement_kind;
    register s32 move_result;
    register u16 *move_state;
    DungeonGlobalStatus *updated_state;
    register u8 *anim_table;
    register s32 facing_offset;

    globals = &g_game_work;
    clear_pending_item_action_state();
    move_result = classify_adjacent_tile_height(map->facing, move_mode, actor, map->ground_height, 0x20);
    movement_kind = (s16)move_result;
    if (movement_kind > 0) {
        obj->action_phase = 0;
        update_map_cell_flags_with_item_limit(actor->tile_x, actor->tile_y, 0x300);
        {
            u8 *x_offsets;
            s16 step_index;

            step_index = (map->facing >> 8) & 0xE;
            x_offsets = ((u8 *)dir_step_x);
            actor->tile_x = actor->tile_x + x_offsets[step_index];
            actor->tile_y = actor->tile_y + ((u8 *)dir_step_y)[step_index];
        }
        cycle_map_cell_flags(actor->tile_x, actor->tile_y, 0x300);

        move_state = (u16 *)&g_dungeon_status;
        move_state[1] |= 8;
        obj->unk_8C.word = 0;

        if (movement_kind != 4) {
            if (system_update_flags & 2) {
                void *anim_entry;

                move_state[1] |= 0x80;
                anim_table = actor_default_frames;
                if (actor->frameTable != anim_table) {
                    actor->frameTable = anim_table;
                    facing_offset = (globals->view.camera_rotation.parts.viewAngle + map->facing + 0x100) >> 7;
                    anim_entry = anim_table + (facing_offset & 0x1C);
                    select_record_entry_and_value(actor, *(void **)anim_entry, 0);
                }
            } else if ((globals->buttons & 0x20) && check_action_available_without_nearby_actor()) {
                register u8 *alternate_anim;

                move_state[1] |= 0x80;
                alternate_anim = actor_default_frames;
                actor->frameTable = alternate_anim;
                facing_offset = (globals->view.camera_rotation.parts.viewAngle + map->facing + 0x100) >> 7;
                select_record_entry_and_value(actor, *(void **)(alternate_anim + (facing_offset & 0x1C)), 0);
            } else {
                move_result = 5;
                obj->action_phase = 10;
            }
        }

        {
            s16 move_kind;

            updated_state = &g_dungeon_status;
            move_kind = (s16)move_result;
            if ((updated_state->flags & 0x80) || move_kind == 1) {
                process_unflagged_linked_entries_alt(map->next_actor_header);
                process_unflagged_linked_entries(map->next_actor_header);
                if (!(updated_state->flags & 0x80)) {
                    actor->frameTable = actor_default_frames;
                    facing_offset = (g_game_work.view.camera_rotation.parts.viewAngle + map->facing + 0x100) >> 7;
                    select_record_entry_and_value(actor, *(void **)(actor_default_frames + (facing_offset & 0x1C)), 0);
                    obj->action_id = 0x35;
                } else {
                    obj->action_id = 0x35;
                }
                updated_state->movement_frames_left = 8;
            } else {
                obj->action_state_flags |= 0xC;
                actor->frameTable = actor_default_frames + 0x20;
                facing_offset = (g_game_work.view.camera_rotation.parts.viewAngle + map->facing + 0x100) >> 7;
                select_record_entry_and_value(actor, *(void **)((actor_default_frames + 0x20) + (facing_offset & 0x1C)), 0);
                if (move_kind < 4) {
                    obj->unk_A0.parts.high |= 1;
                } else if (move_kind == 2 || move_kind == 4) {
                    obj->action_phase = 8;
                }
                check_tile_entry_at_adjusted_height(obj, move_mode, actor, map);
                {
                    g_dungeon_status.movement_frames_left = 8;
                    obj->action_id = 0x36;
                    obj->action_timer = 2;
                    map->flags1C |= 0x40000000;
                    append_packed_action_record(map, 8, 0, 0);
                }
                return;
            }
            append_packed_action_record(map, 8, 0, 0);
        }
    } else {
        u8 *idle_anim;

        idle_anim = actor_default_frames;
        actor->frameTable = idle_anim;
        facing_offset = (globals->view.camera_rotation.parts.viewAngle + map->facing + 0x100) >> 7;
        select_record_entry_and_value(actor, *(void **)(idle_anim + (facing_offset & 0x1C)), 0);
        obj->unk_8C.word = (s32)destination_motion_resume_address;
        return;
    }

    check_tile_entry_at_adjusted_height(obj, move_mode, actor, map);
    map->flags1C |= 0x40000000;
    g_dungeon_status.flags |= 0x812;
}
